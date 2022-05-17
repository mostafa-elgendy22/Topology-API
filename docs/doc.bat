del *.pdf
doxygen
cd latex
latex refman.tex
dvipdfm refman.dvi
copy refman.pdf ..
cd ..
rd /s /q latex
rename refman.pdf topology_api_documentation.pdf