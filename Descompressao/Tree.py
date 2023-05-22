class Tree:
    def __init__(self,chave,esq,dir):
        self.chave = chave
        self.esq   = esq
        self.dir   = dir
        self.e_no  = (chave.__len__() == 1)

def createTree(pre, sim):
    tam = pre.__len__()
    if tam == 1:
        return Tree(pre[0], None, None)
    j = None
    for i in range(tam):
        if pre[0] == sim[i]:
            j = i
            break
    new     = Tree(pre[0], None, None)
    new.esq = createTree(pre[1:j+1],sim[0:j])
    new.dir = createTree(pre[j+1:],sim[j+1:])
    
    return new

def printPreOrdem(tree):
    if tree != None:
        print(tree.chave, end=" ")
        printPreOrdem(tree.esq)
        printPreOrdem(tree.dir)

def PrintarMsg(T, coded_msg):
    t = T
    for i in range(coded_msg.__len__()):
        if coded_msg[i] == '1':
            t = t.dir
        else:
            t = t.esq
        
        if t.e_no:
            print(t.chave, end='')
            t = T
