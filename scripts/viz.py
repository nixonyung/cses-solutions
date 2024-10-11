import sys
from pathlib import Path

import graphviz

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
        start, end = edge.split()
        g.edge(start, end)
        # g.edge(start, end, xlabel=weight)
    g.render()
