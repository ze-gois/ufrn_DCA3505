# Verifica se a visualizer.so agora encontra o símbolo
echo Verifica se a visualizer.so agora encontra o símbolo
nm -D ./build/libgraph_visualization.so | (grep graph_edge_get_from && echo "<blank>")
echo nm -D ./build/libgraph_visualization.so | (grep graph_edge_get_from && echo "<blank>")
# Deve mostrar: U graph_edge_get_from
echo Deve mostrar: U graph_edge_get_from

# Verifica se a libgraph exporta corretamente
echo Verifica se a libgraph exporta corretamente
nm -D ./build/libgraph.so | ( grep graph_edge_get_from && echo "<blank>")
echo nm -D ./build/libgraph.so | ( grep graph_edge_get_from && echo "<blank>")
# Deve mostrar: T graph_edge_get_from
echo Deve mostrar: T graph_edge_get_from

# Opcional: verificar se executável carrega `graph.so`
echo Opcional: verificar se executável carrega "graph.so"
ldd ./build/t02_classic_deadlock | ( grep graph && echo "<blank>")
echo ldd ./build/t02_classic_deadlock | ( grep graph && echo "<blank>")
