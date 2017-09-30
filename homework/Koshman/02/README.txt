	When parsing terms the pointer needs to move backwards because in case of recursion the expression is evaluated from bottom up. So instead of

10/2/5 -> 10/(2/5) -> 10/0 -> error

	We want to get

10/2/5 -> (10/2)/5 -> 5/5 -> 1

	When parsing expressions the order doesn't matter since

expr1 + expr2 = expr1 + expr2

	and binary minus is split up into plus and unary minus:

expr1 - expr2 = expr1 + expr3

	Where first term of expr3 has a unary minus in front of it
