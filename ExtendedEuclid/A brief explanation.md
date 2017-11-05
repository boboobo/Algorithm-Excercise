Extended Euclid's algorithm is implemented through the following process.

extended_Euclid(a,b)
input : positive integer a, b (a >= b >= 0)
output : integer (x,y,d) in here, ax + by = d = gcd(a,b)

if b = 0, 
    return (1, 1, a) ? x = 1, y = 1, d = a
(x¡¯, y¡¯, d) = extended_Euclid(b, a % b)
return (y¡¯, x¡¯ ?  ?a/b? * y¡¯, d)


Extended Euclid algorithm is essentially similar to the Euclid algorithm.

Whereas Euclid algorithm attaining gcd(a,b) if a, b are given,
Extended euclid algorithm attaing x,y,d of ax+by=d=gcd(a,b)