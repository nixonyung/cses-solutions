import re
import sys
from pathlib import Path
from typing import TextIO

INCLUDE_DIR = Path("/repo/include")
OUT_DIR = Path("/out")
OUT_FILE = OUT_DIR / "submission.cpp"


def _write_file(
    src_path: Path,
    out_fp: TextIO,
    included_header_files: set[str],
):
    for line in src_path.read_text().splitlines():
        if (m := re.fullmatch(r"#include \"(?P<header_filename>.*)\"", line)) is not None:
            header_filename = str(m.group("header_filename"))
            if header_filename not in included_header_files:
                _write_file(
                    src_path=INCLUDE_DIR / header_filename,
                    out_fp=out_fp,
                    included_header_files=included_header_files,
                )
                included_header_files.add(header_filename)
        else:
            out_fp.write(line)
            out_fp.write("\n")
    out_fp.write("\n")


def write_file(src_path: Path):
    included_header_files = set[str]()
    with (OUT_DIR / "submission.cpp").open("w") as fp:
        _write_file(src_path=src_path, out_fp=fp, included_header_files=included_header_files)


if __name__ == "__main__":
    write_file(src_path=Path(sys.argv[1]))
