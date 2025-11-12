def func(callback): callback(42)
if __name__ == '__main__': func(lambda x: print(x))