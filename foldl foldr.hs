foldr f z []		= z
foldr f z (x:xs)	= x `f` foldr f z xs

-- foldr (+) z x:xs
-- (x1 + (x2 + ...(xn + z)))

foldl f z []		= z
foldl f z (x:xs)	= let z' = z `f` x
			  in foldl f z' xs

-- foldl (+) z x:xs
-- (((z + x1) + x2)... + xn)
