input de um move: (e/d) (u/d)
no max 4 jogadas possiveis, esquerda/direita, cima/baixo
rainha pode andar 1 casa para tras

numerar posicoes
(d,u) - 0
(d,d) - 1
(e,d) - 2
(e,u) - 3

eval > pos para player1

passar eval para minimax
simplificar minimax !?

vhdbfgv
1_1 || 1_3_5_6
1_3

mcts(50) 500000 vs minimax 4, 1 minimax
w: 121
d: 28
l: 51

mcts(50) 200000 vs minimax 4, 1 minimax
w: 112
d: 34
l: 54

mcts(50) 100000 vs minimax 4, 1 minimax
w: 107
d: 36
l: 57

mcts(50) 50000 vs minimax 4, 1 minimax
w: 78
d: 58
l: 64
