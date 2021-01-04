from random import randint

def make_interval(minl=1, maxl=10, minr=1, maxr=20):
    return randint(minl, maxl), randint(minr, maxr)

if __name__ == '__main__':
    print("Generate random intervals")
    minl = int(input("minl > "))
    maxl = int(input("maxl > "))
    minr = int(input("minr > "))
    maxr = int(input("maxr > "))
    while True:
        print(make_interval(minl, maxl, minr, maxr))
        input()
