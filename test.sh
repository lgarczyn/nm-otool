./ft_nm $1 > t1.txt
otool -t $1 > t2.txt
diff t1.txt t2.txt
