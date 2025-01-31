import sys
from pathlib import Path

import graphviz  # type:ignore

OUT_DIR = Path("./out")


if __name__ == "__main__":
    g = graphviz.Digraph(
        name="graph",
        format="png",
        graph_attr={
            "bgcolor": "black",
        },
        node_attr={
            "color": "white",
            "fontcolor": "white",
            "overlap": "scale",  # (ref.) [laying out a large graph with graphviz](https://stackoverflow.com/questions/13417411/laying-out-a-large-graph-with-graphviz)
        },
        edge_attr={
            "color": "white",
            "fontcolor": "white",
        },
    )

    for line in Path(sys.argv[1]).read_text().splitlines()[1:]:
        tokens = line.split()
        if len(tokens) == 2:
            g.edge(tokens[0], tokens[1])  # type:ignore
        elif len(tokens) == 3:
            g.edge(tokens[0], tokens[1], xlabel=tokens[2])  # type:ignore
        else:
            raise Exception(f"unexpected edge format: got {len(tokens)} tokens")
    g.render(directory=OUT_DIR)  # type:ignore
