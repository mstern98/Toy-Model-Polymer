import numpy as np
import matplotlib.pyplot as plt
import os

from glob import iglob
from collections import Counter
from subprocess import call
from time import sleep

def main(x, y, s, S):
	p = np.arange(-.25, .25 + .025, .025)
	N = np.arange(10, 100 + 10, 10)

	p_dict = {}
	N_dict = {}
	for n in N:
		for i in p:
			if not os.path.isdir(str(n)):
				call(["mkdir", str(n)])
			N_ = "-N " + str(n)
			P_ = "-p " + str(i)
			x_ = "-x " + str(x)
			y_ = "-y " + str(y)
			s_ = "-s " + str(s)
			S_ = "-S " + str(S)
			call(["./polymer", x_, y_, s_, S_, N_, P_])
			sleep(1)
			radii = []
			for fp in iglob("*.dat"):
				with open(fp) as f:
					lines = f.readlines()
					a = lines[0].strip("\n").split(" ")
					b = lines[len(lines) - 1].strip("\n").split(" ")
					r = np.sqrt(np.power(float(a[0]) - float(b[0]), 2) + np.power(float(a[1]) - float(b[1]), 2))
					radii.append(r)
				os.remove(fp)

			q = dict(Counter([x//1 for x in radii]))
			fig = plt.figure(("Radii_(N=%s, p=%s)" % (n, i)))
			plt.xlabel("Radii of polymers")
			plt.ylabel("Number of paths")
			plt.bar(list(q.keys()), list(q.values()), align='edge', width = .3)
			plt.savefig(("%s/Histogram_of_Radii_(N=%s, p=%s).png" % (n, n, i)))
			plt.close(fig)
		
			if len(radii) != 0:	
				mean = np.mean(radii)

				if n not in N_dict:
					N_dict.setdefault(n, [])
				if i not in p_dict:
					p_dict.setdefault(i, [])

				N_dict[n].append(mean)
				p_dict[i].append(mean)
	
	fig = plt.figure("Radii vs P")
	for xe, ye in p_dict.items():
		xAxis = [xe] * len(ye)
		plt.xlabel("Probility p")
		plt.ylabel("Mean Radii of Polymers")
		plt.scatter(xAxis, ye)
	plt.savefig(("Histogram_of_Mean_Radii_vs_P.png" ))

	fig = plt.figure("Radii vs N")
	for xe, ye in N_dict.items():
		xAxis = [xe] * len(ye)
		plt.xlabel("N")
		plt.ylabel("Mean Radii of Polymers")
		plt.scatter(xAxis, ye)
	plt.savefig(("Histogram_of_Mean_Radii_vs_N.png" ))


if __name__ == "__main__":
	x = 20
	y = 20
	s = 40
	S = 100
	main(x, y, s, S)
