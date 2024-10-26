import sys
from pathlib import Path

import graphviz

OUT_DIR = Path("/out")

g = graphviz.Digraph(  # `graphviz.Graph` for undirected graph
    name="graph",
    format="png",
    graph_attr={
        "bgcolor": "black",
    },
    node_attr={
        "color": "white",
        "fontcolor": "white",
        "overlap": "scale",
    },
    edge_attr={
        "color": "white",
        "fontcolor": "white",
        "splines": "line",
    },
)

if __name__ == "__main__":
    for edge in Path(sys.argv[1]).read_text().splitlines()[1:]:
        tokens = edge.split()
        match len(tokens):
            case 2:
                g.edge(str(int(tokens[0]) - 1), str(int(tokens[1]) - 1))
            case 3:
                g.edge(str(int(tokens[0]) - 1), str(int(tokens[1]) - 1), xlabel=tokens[2])
    g.render(directory=OUT_DIR)
