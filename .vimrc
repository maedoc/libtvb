" project specific vim settings
"
" I (@maedoc) use the following Vim plugins which covers
" everything I'd want from an IDE:
"
" - github.com/Valloric/YouCompleteMe
" - scrooloose/syntastic
" - tpope/vim-fugitive
" - kien/ctrlp.vim

set nu rnu ai foldmethod=marker

map <F3> :ls<cr>:b<space>
map <F4> :YcmForceCompileAndDiagnostics<cr>
map <F5> :vimgrep TODO src/*.c include/*.h<cr>:cw<cr>
