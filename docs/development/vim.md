
## Add GitHub hosts


```shell
sudo vim /etc/hosts

# GitHub Host Start

185.199.108.154              github.githubassets.com
140.82.112.22                central.github.com
185.199.108.133              desktop.githubusercontent.com
185.199.108.153              assets-cdn.github.com
185.199.108.133              camo.githubusercontent.com
185.199.108.133              github.map.fastly.net
199.232.69.194               github.global.ssl.fastly.net
140.82.113.4                 gist.github.com
185.199.108.153              github.io
140.82.114.3                 github.com
140.82.114.6                 api.github.com
185.199.108.133              raw.githubusercontent.com
185.199.108.133              user-images.githubusercontent.com
185.199.108.133              favicons.githubusercontent.com
185.199.108.133              avatars5.githubusercontent.com
185.199.108.133              avatars4.githubusercontent.com
185.199.108.133              avatars3.githubusercontent.com
185.199.108.133              avatars2.githubusercontent.com
185.199.108.133              avatars1.githubusercontent.com
185.199.108.133              avatars0.githubusercontent.com
185.199.108.133              avatars.githubusercontent.com
140.82.113.10                codeload.github.com
52.217.166.105               github-cloud.s3.amazonaws.com
52.217.164.49                github-com.s3.amazonaws.com
54.231.133.129               github-production-release-asset-2e65be.s3.amazonaws.com
52.216.134.83                github-production-user-asset-6210df.s3.amazonaws.com
52.217.105.188               github-production-repository-file-5c1aeb.s3.amazonaws.com
185.199.108.153              githubstatus.com
64.71.144.202                github.community
185.199.108.133              media.githubusercontent.com

# Please Star : https://github.com/ineo6/hosts
# Mirror Repo : https://gitee.com/ineo6/hosts
# Update at: 2022-03-10 12:15:33

```

## Download Vundle


```shell
git clone https://e.coding.net/paddyhuang/linux-source-code/Vundle.vim.git ~/.vim/bundle/Vundle.vim

```

## Download dependencies


```shell
# Using apt
sudo apt install nodejs npm
# node / npm
curl -sL install-node.now.sh | sudo bash
# Or install nvm
curl https://raw.githubusercontent.com/creationix/nvm/master/install.sh | bash

# coc.vim
# https://github.com/neoclide/coc.nvim/wiki/Language-servers
# clangd
# https://clangd.llvm.org/installation.html
sudo apt install clangd-12
# This will install clangd as /usr/bin/clangd-12. Make it the default clangd:
sudo update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-12 100

sudo apt install python3-pip
sudo apt install python3.8-venv
```

## Compose .vimrc


```
set encoding=utf-8
set nocompatible              " required
filetype off                  " required
syntax on
set fdm=indent

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" Add all your plugins here (note older versions of Vundle used Bundle instead of Plugin)

" File/folder navigation
Plugin 'scrooloose/nerdtree'

Plugin 'SirVer/ultisnips'

Plugin 'honza/vim-snippets'

Plugin 'neoclide/coc.nvim'

" All of your Plugins must be added before the following line
call vundle#end()            " required

filetype plugin indent on    " required

" Ignore files in NERDTree
let NERDTreeIgnore=['\.pyc$', '\~$'] "ignore files in NERDTree
" NERDTree config
map <C-t> :NERDTreeToggle<CR>

au BufNewFile,BufRead *.py set tabstop=4 softtabstop=4 shiftwidth=4 textwidth=79 expandtab autoindent fileformat=unix

au BufNewFile,BufRead *.js   set tabstop=2 softtabstop=2 shiftwidth=2
au BufNewFile,BufRead *.html set tabstop=2 softtabstop=2 shiftwidth=2
au BufNewFile,BufRead *.css  set tabstop=2 softtabstop=2 shiftwidth=2

au BufNewFile,BufRead *.cpp set tabstop=4 softtabstop=4 shiftwidth=4 textwidth=79 expandtab autoindent fileformat=unix
au BufNewFile,BufRead *.hpp set tabstop=4 softtabstop=4 shiftwidth=4 textwidth=79 expandtab autoindent fileformat=unix

"split navigations
nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>

imap jk <esc>
imap kj <esc>

" Incase of backspace not working
set backspace=2

let g:UltiSnipsExpandTrigger="<tab>"
" 使用 tab 切换下一个触发点，shit+tab 上一个触发点
let g:UltiSnipsJumpForwardTrigger="<tab>"
let g:UltiSnipsJumpBackwardTrigger="<S-tab>"
" 使用 UltiSnipsEdit 命令时垂直分割屏幕
let g:UltiSnipsEditSplit="vertical"

```

- <C-t> => toggle NERDTree

- :CocList marketplace => install/uninstall package

- :CocInstall / CocUninstall [package name]

- :CocList extensions => check installed packages

- :CocUpdate => update coc packages

- :PluginInstall



## Coc.vim packages


```
:CocInstall coc-jedi # Python
:CocInstall coc-clangd # C/C++
:CocInstall coc-cmake

```


