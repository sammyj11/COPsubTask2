import numpy as np

def foo(m,n,k,test,num):
    for tst in range(test):
      arr1 = [[0]*n for i in range(m)]
      arr2 = [[0]*k for i in range(n)]
      arr3 = [[0]*k for i in range(m)]
      for i in range (m):
              uniform_nbrs = np.around(np.random.uniform(size=n), decimals=5)
              for j in range(n):
                arr1[i][j] = uniform_nbrs[j]
      for i in range(n):
          uniform_nbrs = np.around(np.random.uniform(size=k), decimals=5)
          for j in range(k):
              arr2[i][j] = uniform_nbrs[j]

      for i in range(m):
          uniform_nbrs = np.around(np.random.uniform(size=k), decimals=5)
          for j in range(k):
              arr3[i][j] = uniform_nbrs[j]

      m1 = open("t{}.m1.txt".format(num),"w")        

      print(n,file=m1)
      print(m,file=m1)
      for i in range (m):
          for j in range(n):
              print(arr1[i][j],file=m1)
      m1.close()

      m2 = open("t{}.m2.txt".format(num),"w")        

      print(k,file=m2)
      print(n,file=m2)
      for i in range(n):
          for j in range(k):
              print(arr2[i][j],file=m2)
      m2.close()

      m3 = open("t{}.m3.txt".format(num),"w")        

      print(k,file=m3)
      print(m,file=m3)
      for i in range(m):
          for j in range(k):
              print(arr3[i][j],file=m3)
      m3.close()

def foo2(n,x,y):
    return foo(n,n,n,x,y)

foo2(3,1,10)