set shell := ["bash", "-uc"]

alias e := edit
alias c := compile
alias f := flash

default:
    @just --list

edit:
    nvim kb/keymaps/dwgrth/keymap.c

compile:
    qmk compile

lsp:
    qmk compile --compiledb

flash:
    @echo 'r-ctrl & l-super & esc -> qk_boot'
    qmk flash

clean:
    qmk clean
