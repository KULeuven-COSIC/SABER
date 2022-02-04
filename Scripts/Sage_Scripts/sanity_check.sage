#!/usr/bin/env sage

n = int(sys.argv[1])
q = int(sys.argv[2])
numinputs = int(sys.argv[3])

set_random_seed(1) # reproducibility
proof.all(False)


try:
  os_cores = len(os.sched_getaffinity(0))
except:
  os_cores = cpu_count()
os_cores = os.getenv('CORES',default=os_cores)
os_cores = int(os_cores)
if os_cores < 1: os_cores = 1


import fpylll

# not just for speed; also deals with "cannot open strategies file" fpylll bug
try:
  fn = fpylll.BKZ.DEFAULT_STRATEGY
  if not fn.startswith('/'):
    fn = fpylll.BKZ.DEFAULT_STRATEGY_PATH+'/'+fn
except TypeError:
  fn = fpylll.BKZ.DEFAULT_STRATEGY
  if not fn.startswith(b'/'):
    fn = fpylll.BKZ.DEFAULT_STRATEGY_PATH+b'/'+fn
precomputed_bkz_strategies = fpylll.load_strategies_json(fn)

def bkz(M,beta):
  return M.BKZ(block_size=beta,strategies=precomputed_bkz_strategies)


from sage.doctest.util import Timer
timer = Timer()

Zx.<x> = ZZ[]
R = Zx.quotient(x^n+1)

def reduce(r):
  assert r in R
  return R(sum((r[i]%q)*x^i for i in range(n)))
  # "r %= q" in Sage sometimes produces wrong reduction mod q
  # for example, try this: R.<x> = ZZ[]; (-x) % 3

def divq(r):
  assert r in R
  assert all(r[i]%q == 0 for i in range(n))
  return R(sum(ZZ(r[i]/q)*x^i for i in range(n)))

def randomsubset(n,m):
  L = [2*randrange(2^64)+1 for j in range(m)] + [2*randrange(2^64) for j in range(n-m)]
  L.sort()
  return tuple(j for j in range(n) if L[j]%2 == 1)


@parallel(ncpus=os_cores)
def doit(rounding,secreta1,secreta2,secrete1,secrete2,secretr1,secretr2,G11,G12,G21,G22,A1,A2):
  result = []

  for r in [G11,G12,G21,G22,A1,A2]:
    assert all(r[i]>=0 for i in range(n))
    assert all(r[i]<q for i in range(n))

  for m in range(n,2*n+1,2):
    d = m+1+2*n

    S = randomsubset(2*n,m)
    assert S == tuple(sorted(S))
    assert len(S) == m
    assert all(j >= 0 for j in S)
    assert all(j < 2*n for j in S)
    
    def Extract(e1,e2):
      assert e1 in R
      assert e2 in R
      e1e2 = list(e1)+list(e2)
      return [e1e2[j] for j in S]
    
    def P(z,a1,a2,r1,r2):
      assert z in ZZ
      assert a1 in R
      assert a2 in R
      assert r1 in R
      assert r2 in R
      e1 = z*A1-a1*G11-a2*G21+r1*q
      e2 = z*A2-a1*G12-a2*G22+r2*q
      return Extract(e1,e2)+[z]+list(a1)+list(a2)
    
    secretvector = Extract(secrete1,secrete2)+[1]+list(secreta1)+list(secreta2)
    assert secretvector == P(1,secreta1,secreta2,secretr1,secretr2)

    Cinbasis = []
    Cinbasis += [(1,R(0),R(0),R(0),R(0))]
    for i in range(n):
      Cinbasis += [(0,R(x^i),R(0),R(0),R(0))]
    for i in range(n):
      Cinbasis += [(0,R(0),R(x^i),R(0),R(0))]
    for i in range(len(S)):
      if S[i] < n:
        Cinbasis += [(0,R(0),R(0),R(x^S[i]),R(0))]
      else:
        Cinbasis += [(0,R(0),R(0),R(0),R(x^(S[i]-n)))]
        
    Coutbasis = [P(z,a1,a2,r1,r2) for z,a1,a2,r1,r2 in Cinbasis]
    
    assert d == len(Cinbasis)
    assert d == len(Coutbasis)
    
    M = matrix(Coutbasis)
    assert abs(det(M)) == q^m
    
    success = False
    time = 0
    
    for beta in range(2,21,2):
      if not success:
        timer.start()
        if beta == 2:
          M = M.LLL()
        else:
          M = bkz(M,beta)
        time += timer.stop().cputime

        # fpylll BKZ doesn't always put shortest basis vector first
        v = M[0]
        for i in range(1,M.nrows()):
          if M[i]*M[i] < v*v:
            v = M[i]

        if v[m] < 0: v = -v
      
        a1 = R(list(v[m+1:m+1+n]))
        a2 = R(list(v[m+1+n:m+1+2*n]))

        if (a1,a2) == (secreta1,secreta2):
          success = True

      result += [(rounding,m,d,beta,success,time)]

  return result

  
def randomsmallcoeff():
  return sum(randrange(2) for coin in range(4)) - 2

def randomsmall():
  return R([randomsmallcoeff() for i in range(n)])

def randomq():
  return R([randrange(q) for i in range(n)])

def round8offset(r):
  result = R([((4-r[i])%8)-4 for i in range(n)])
  assert all(result[i] >= -4 for i in range(n))
  assert all(result[i] <= 3 for i in range(n))
  assert all((r[i]+result[i])%8 == 0 for i in range(n))
  return result

def noise8():
  return R([randrange(-4,4) for i in range(n)])

def inputs():
  for i in range(numinputs):
    secreta1 = randomsmall()
    secreta2 = randomsmall()
   
    G11 = randomq()
    G12 = randomq()
    G21 = randomq()
    G22 = randomq()

    for rounding in False,True:
      Z1 = secreta1*G11+secreta2*G21
      Z2 = secreta1*G12+secreta2*G22

      if rounding:
        secrete1 = round8offset(Z1)
        secrete2 = round8offset(Z2)
      else:
        secrete1 = noise8()
        secrete2 = noise8()

      Z1 += secrete1
      Z2 += secrete2

      A1 = reduce(Z1)
      A2 = reduce(Z2)
      secretr1 = divq(Z1-A1)
      secretr2 = divq(Z2-A2)
    
      yield rounding,secreta1,secreta2,secrete1,secrete2,secretr1,secretr2,G11,G12,G21,G22,A1,A2

def strpoly(r):
  return str(list(r)).replace(' ','')

stats = {}

for control,result in sorted(list(doit(inputs()))):
  rounding,secreta1,secreta2,secrete1,secrete2,secretr1,secretr2,G11,G12,G21,G22,A1,A2 = control[0]
  for rounding,m,d,beta,success,time in result:
    sys.stdout.write(
      'n %d q %d rounding %s m %d d %d beta %d success %s time %.6f a1 %s a2 %s e1 %s e2 %s G11 %s G12 %s G21 %s G22 %s A1 %s A2 %s\n'
      % (n,q,rounding,m,d,beta,success,time,strpoly(secreta1),strpoly(secreta2),strpoly(secrete1),strpoly(secrete2),strpoly(G11),strpoly(G12),strpoly(G21),strpoly(G22),strpoly(A1),strpoly(A2))
    )

    if (m,d,beta,rounding) not in stats:
      stats[m,d,beta,rounding] = []
    stats[m,d,beta,rounding] += [success]

for m,d,beta,rounding in sorted(stats):
  S = stats[m,d,beta,rounding]
  assert len(S) == numinputs
  print('n %d q %d rounding %s m %d d %d beta %d percentage %.9f numinputs %d'
    % (n,q,rounding,m,d,beta,sum(S)/len(S),len(S)))
