import multiprocessing
import subprocess
import sys
from itertools import zip_longest
from pathlib import Path
from time import perf_counter
from typing import NamedTuple

MAIN_PATH = Path("./out/main")


class CheckResult(NamedTuple):
    ok: bool
    duration: float


def check(
    tests_dir: Path,
    test_id: int,
):
    start_time = perf_counter()
    with (
        (tests_dir / f"{test_id}.in").open("r") as fp_in,
        (tests_dir / f"{test_id}.out").open("rb") as fp_out,
    ):
        # (ref.) [live output from subprocess command](https://stackoverflow.com/questions/18421757/live-output-from-subprocess-command)
        p = subprocess.Popen(
            [MAIN_PATH],
            stdin=fp_in,
            stdout=subprocess.PIPE,
        )
        if not p.stdout:
            raise Exception("unexpected error: stdout is None, check if stdout is set to subprocess.PIPE")

        for row, (line_in, line_out) in enumerate(zip_longest(p.stdout, fp_out, fillvalue=b"")):
            for col, (ch_in, ch_out) in enumerate(zip_longest(line_in, line_out, fillvalue=0)):
                if ch_in != ch_out:
                    print(
                        f"test {test_id:02} failed at {(tests_dir / f'{test_id}.out')}:{row + 1}:{col + 1}, expected '{chr(ch_out)}' but got '{chr(ch_in)}'"
                    )
                    return CheckResult(ok=False, duration=0.0)
        duration = perf_counter() - start_time
        print(f"test {test_id:02} ok, took {duration:.4f}s")
        return CheckResult(ok=True, duration=duration)


if __name__ == "__main__":
    tests_dir = Path(sys.argv[1]).parent / "tests"
    if len(sys.argv) >= 3:
        test_id = int(sys.argv[2])

        # run main without diffing output
        with (tests_dir / f"{test_id}.in").open("r") as fp_in:
            subprocess.run([MAIN_PATH], stdin=fp_in)
    else:
        with multiprocessing.Pool() as pool:
            results = pool.starmap(
                check,
                [
                    (
                        tests_dir,
                        test_id,
                    )
                    for test_id in sorted(int(test_path.stem) for test_path in tests_dir.glob("*.in"))
                ],
            )
        if all(res.ok for res in results):
            print(f"all tests ok, max_duration = {max(res.duration for res in results):.4f}s")
        else:
            print("found failing tests")
