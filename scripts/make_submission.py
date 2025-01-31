import re
import sys
from pathlib import Path
from typing import TextIO

INCLUDE_DIR = Path("./include")
OUT_DIR = Path("./out")


def write_file(
    src_path: Path,
    out_fp: TextIO,
    included_header_file_paths: set[str] | None = None,
):
    if included_header_file_paths is None:
        included_header_file_paths = set()

    for line in src_path.read_text().splitlines():
        if m := re.fullmatch(r"#include \"(?P<header_file_path>.+)\"", line):
            header_file_path = str(m.group("header_file_path"))
            if header_file_path not in included_header_file_paths:
                write_file(
                    src_path=INCLUDE_DIR / header_file_path,
                    out_fp=out_fp,
                    included_header_file_paths=included_header_file_paths,
                )
                included_header_file_paths.add(header_file_path)
        else:
            out_fp.write(line)
            out_fp.write("\n")
    out_fp.write("\n")


if __name__ == "__main__":
    write_file(
        src_path=Path(sys.argv[1]),
        out_fp=(OUT_DIR / "submission.cpp").open("w"),
    )
