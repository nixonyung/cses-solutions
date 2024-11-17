import sys
from pathlib import Path

import graphviz  # type:ignore

OUT_DIR = Path("/out")


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

    for edge in Path(sys.argv[1]).read_text().splitlines()[1:]:
        tokens = edge.split()
        src = str(int(tokens[0]) - 1)
        dest = str(int(tokens[1]) - 1)
        weight = None
        if len(tokens) >= 3:
            weight = tokens[2]

        g.edge(src, dest, xlabel=weight)
    g.render(directory=OUT_DIR)
