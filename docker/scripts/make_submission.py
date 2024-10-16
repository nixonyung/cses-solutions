import re
import sys
from pathlib import Path
from typing import TextIO

INCLUDE_DIR = Path("/repo/include")
OUT_DIR = Path("/out")


included_header_files = set[str]()


def write_file(
    src_path: Path,
    out_file: TextIO,
):
    for line in src_path.read_text().splitlines():
        if (m := re.fullmatch(r"#include \"(?P<header_file>.*)\"", line)) is not None:
            header_file = m.group("header_file")
            if header_file not in included_header_files:
                write_file(
                    src_path=INCLUDE_DIR / m.group("header_file"),
                    out_file=out_file,
                )
                included_header_files.add(header_file)
        else:
            fp.write(line)
            fp.write("\n")
    fp.write("\n")


if __name__ == "__main__":
    with (OUT_DIR / "submission.cpp").open("w") as fp:
        write_file(
            src_path=Path(sys.argv[1]),
            out_file=fp,
        )
