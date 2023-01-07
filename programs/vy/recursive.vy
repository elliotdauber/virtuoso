def factorial n {
    if n {
        return n * <factorial (n - 1)>;
    };
    return 1;
}

def main {
    n = 6;
    res = <factorial n>;
    print res;
    return 0;
}