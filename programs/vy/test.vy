def add a b {
    return 1 + 2;
}

def sub a b {
    return a - b;
}

def locs a b {
    x = a + b;
    return x;
}

def main {
    x = 5;
    y = 10;
    z = <add x y>;
    w = z + x;
    print w;
    return 0;
}