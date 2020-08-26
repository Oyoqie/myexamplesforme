foldr f z []	= z
foldr f z x:xs	= x `f` foldr f z xs

foldl f z []	= z
foldl f z x:xs	= let z' = z `f` x
				  in foldl f z' xs