def fncall a b c {
    x = a + b;
    y = x * c;
    return y;
}

def main {
    x = <fncall 1 2 3>;
    print x;
    return 0;
}