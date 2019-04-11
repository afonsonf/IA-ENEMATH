class Board:
    #add more if needed
    __slots__ = ['playsStack','best_play','depth']

    def __init__(self):
        self.playsStack = []
        self.movesStack = []
        self.depth = 0

        #initialize board

        return

    def dup(self):
        board = Board()
        if len(self.playsStack) > 0: board.playsStack.append(self.playsStack[len(self.playsStack)-1])
        board.depth = self.depth

        #copy board

        return board

    def play(self, p):
        self.playsStack.append(p.dup())

        #play p in board

        return


    def rmplay(self):
        p = self.playsStack[len(self.playsStack)-1]
        self.playsStack.pop()

        #rm play p from board

        return

    def getPlays(self, player):
        res = []
        #add playable plays to res

        return res

    def whoWins(self, next_player):
        # next player is false and loses return  1 (true wins)
        # next player is true  and loses return -1 (false wins)
        # else return 0

        return 0

    def isDraw(self):
        #check if draw

        return False

    def gameOver(self, next_player):
        if self.whoWins(next_player) or self.isDraw(): return True
        return False

    def eval_board(self):
        value = 0

        return value

    def printBoard(self):
        return
