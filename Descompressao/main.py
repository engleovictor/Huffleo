import Tree, sys

def main():
    with open(sys.argv[1]) as f:
        lines    = f.read().splitlines()
        lines[0] = lines[0][10:].split(", ")
        lines[1] = lines[1][10:].split(", ")
        lines[0].pop()
        lines[1].pop()
        T = Tree.createTree(lines[1],lines[0])
        Tree.PrintarMsg(T, lines[2])
        print()


if __name__ == "__main__":
    main()