
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
set foldlevelstart=99

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

" For GUI system
Plugin 'iamcco/markdown-preview.nvim' 

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

"""""""" For GUI system
" set to 1, nvim will open the preview window after entering the markdown buffer
" default: 0
"let g:mkdp_auto_start = 0

" set to 1, the nvim will auto close current preview window when change
" from markdown buffer to another buffer
" default: 1
"let g:mkdp_auto_close = 1

" set to 1, the vim will refresh markdown when save the buffer or
" leave from insert mode, default 0 is auto refresh markdown as you edit or
" move the cursor
" default: 0
"let g:mkdp_refresh_slow = 0

" set to 1, the MarkdownPreview command can be use for all files,
" by default it can be use in markdown file
" default: 0
"let g:mkdp_command_for_global = 0

" set to 1, preview server available to others in your network
" by default, the server listens on localhost (127.0.0.1)
" default: 0
"let g:mkdp_open_to_the_world = 0

" use custom IP to open preview page
" useful when you work in remote vim and preview on local browser
" more detail see: https://github.com/iamcco/markdown-preview.nvim/pull/9
" default empty
"let g:mkdp_open_ip = ''

" specify browser to open preview page
" default: ''
"let g:mkdp_browser = ''

" set to 1, echo preview page url in command line when open preview page
" default is 0
"let g:mkdp_echo_preview_url = 0

" a custom vim function name to open preview page
" this function will receive url as param
" default is empty
"let g:mkdp_browserfunc = ''

" options for markdown render
" mkit: markdown-it options for render
" katex: katex options for math
" uml: markdown-it-plantuml options
" maid: mermaid options
" disable_sync_scroll: if disable sync scroll, default 0
" sync_scroll_type: 'middle', 'top' or 'relative', default value is 'middle'
"   middle: mean the cursor position alway show at the middle of the preview page
"   top: mean the vim top viewport alway show at the top of the preview page
"   relative: mean the cursor position alway show at the relative positon of the preview page
" hide_yaml_meta: if hide yaml metadata, default is 1
" sequence_diagrams: js-sequence-diagrams options
" content_editable: if enable content editable for preview page, default: v:false
" disable_filename: if disable filename header for preview page, default: 0
"let g:mkdp_preview_options = {
    "\ 'mkit': {},
    "\ 'katex': {},
    "\ 'uml': {},
    "\ 'maid': {},
    "\ 'disable_sync_scroll': 0,
    "\ 'sync_scroll_type': 'middle',
    "\ 'hide_yaml_meta': 1,
    "\ 'sequence_diagrams': {},
    "\ 'flowchart_diagrams': {},
    "\ 'content_editable': v:false,
    "\ 'disable_filename': 0
    "\ }

" use a custom markdown style must be absolute path
" like '/Users/username/markdown.css' or expand('~/markdown.css')
"let g:mkdp_markdown_css = ''

" use a custom highlight style must absolute path
" like '/Users/username/highlight.css' or expand('~/highlight.css')
"let g:mkdp_highlight_css = ''

" use a custom port to start server or random for empty
"let g:mkdp_port = ''

" preview page title
" ${name} will be replace with the file name
"let g:mkdp_page_title = '「${name}」'

" recognized filetypes
" these filetypes will have MarkdownPreview... commands
"let g:mkdp_filetypes = ['markdown']

" example
"nmap <C-s> <Plug>MarkdownPreview
"nmap <M-s> <Plug>MarkdownPreviewStop
"nmap <C-p> <Plug>MarkdownPreviewToggle
"""""""" GUI system end
```

- <C-t> => toggle NERDTree

- :CocInstall coc-marketplace

- :CocList marketplace => install/uninstall package

- :CocInstall / CocUninstall [package name]

- :CocList extensions => check installed packages

- :CocUpdate => update coc packages

- :PluginInstall



## Coc.vim packages


```
:CocInstall coc-pyright # Python
:CocInstall coc-clangd  # C/C++
:CocInstall coc-cmake

```


