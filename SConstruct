import os

buildDiscAction = Action('tools/buildDisc.sh > build.log')

env = Environment(
    ENV={'PATH': os.environ['PATH']},
    CPPPATH='mega65-libc/cc65/include',
    CC='cl65')

test = env.Program('bin/fcdemo.c64', [
    'src/test.c',
    'mega65-libc/cc65/src/memory.c',
    'mega65-libc/cc65/src/conio.c',
    'mega65-libc/cc65/src/fcio.c'
])

env.AddPostAction(test, buildDiscAction)
