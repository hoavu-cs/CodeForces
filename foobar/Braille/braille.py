def solution(s):
    # Your code here
    output = ""

    for c in s:
        braille = [0,0,0,0,0,0]
        if c == ' ': # signal space letter
            output += "000000"
        else:
            if c.isupper(): # signal upper case letter
                output += "000001"
                c = c.lower()

            if c == 'w': # handle special case 'w'
                braille[1] = braille[3] = braille[4] = braille[5] = 1
            else:
                if ord(c) in range(ord('k'),ord('t')+1):
                    braille[2] = 1
                elif ord(c) in range(ord('u'),ord('z')+1):
                    braille[2] = braille[5] = 1

                if c in {'a', 'k', 'u'}:
                    braille[0] = 1
                elif c in {'b', 'l', 'v'}:
                    braille[0] = braille[1] = 1
                elif c in {'c', 'm', 'x'}:
                    braille[0] = braille[3] = 1
                elif c in {'d', 'n', 'y'}:
                    braille[0] = braille[3] = braille[4] = 1
                elif c in {'e', 'o', 'z'}:
                    braille[0] = braille[4] = 1
                elif c in {'f', 'p'}:
                    braille[0] = braille[1] = braille[3] = 1
                elif c in {'g', 'q'}:
                    braille[0] = braille[1] = braille[3] = braille[4] = 1
                elif c in {'h', 'r'}:
                    braille[0] = braille[1] = braille[4] = 1
                elif c in {'i', 's'}:
                    braille[1] = braille[3] = 1
                elif c in {'j', 't'}:
                    braille[1] = braille[3] = braille[4] = 1

            # append braille to output
            output += ''.join(map(str, braille))

    return output

print(solution("The quick brown fox jumps over the lazy dog"))
