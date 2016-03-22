# copyright 2016 Apache 2 sddekit authors

"""
git branch -D gh-pages
git init docs
doxygen
cd docs && git add html/* && git mv html/* ./ && git commit -m "add doxygen html"
git fetch docs master:gh-pages
rm -rf docs
"""