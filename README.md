echo "# ntld" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote rm origin
git remote add origin git@github.com:bseazeng/ntld.git
git push -u origin master


