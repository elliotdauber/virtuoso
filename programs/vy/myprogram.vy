def g a b {
    c = a + b;
    print c;
    d = a * b + c;
    print d;
    return a * b + c;
}

def f a b {
    return b - a + 4;
}

def main {
    x = 6;
    y = 2;
    print x;
    z = <g x y>;
    print z;
    return 0;
}