#!/usr/bin/env python3
import subprocess
import time
import os
import statistics
import matplotlib
import math
import numpy as np
import matplotlib.pyplot as plt
from scipy import optimize as op
def main():
    T=0
    T=input('请输入测试次数：')
    T=int(T)
    # type(T)
    # file.write(T)

    with open('testdetail(default)(int).txt','w',encoding='utf-8') as file:

        '''
        flag=input('数据的类型（0为整形，1为浮点）：')
        nlim_l=input('n的下限：')
        nlim_r=input('n的下限：')

        flag=int(flag)
        nlim_l=int(nlim_l)
        nlim_r=int(nlim_r)

        with open('datarequirement.txt', 'w', encoding='utf-8') as file:
            file.write(f"{flag} {nlim_l} {nlim_r}\n")
            file.write("这是第二行内容\n")
        '''
        ns=[]
        nc_times=[]
        rc_times=[]
        np_times=[]
        pr_times=[]
        nc_memories=[]
        rc_memories=[]
        np_memories=[]
        pr_memories=[]
        
        file.write(f"开始性能测试，测试组数: {T}\n")
        
        for i in range(1,T+1):
            file.write(f"======== 第 {i} 次运行 ========\n")
            
            nc_time=0
            rc_time=0
            np_time=0
            pr_time=0
            nc_memory=0
            rc_memory=0
            np_memory=0
            pr_memory=0
            
            subprocess.run(["./dataproducer"], check=True)
            
            with open('testdata.txt','r',encoding='utf-8') as f:
                f.readline()
                tmp_n=int(f.readline().strip())
                ns.append(tmp_n)

            # file.write(f"{tmp_n}\n")

            start_time=time.time()
            subprocess.run(["./qsnc"],check=True)
            end_time=time.time()
            nc_time=end_time-start_time
            
            nc_memory=get_memory_usage()
            
            #/////////////////////////////////////////////////////////////////
            
            start_time=time.time()
            subprocess.run(["./qsrc"],check=True)
            end_time=time.time()
            rc_time=end_time-start_time
            
            rc_memory=get_memory_usage()

            #/////////////////////////////////////////////////////////////////

            start_time=time.time()
            subprocess.run(["./msnp"],check=True)
            end_time=time.time()
            np_time=end_time-start_time
            
            np_memory=get_memory_usage()

            #////////////////////////////////////////////////////////////////

            start_time=time.time()
            subprocess.run(["./mspr"],check=True)
            end_time=time.time()
            pr_time=end_time-start_time
            
            pr_memory=get_memory_usage()

            #////////////////////////////////////////////////////////////////
            
            file.write(f"qsnc结果:\n  时间: {nc_time:.6f}s, 内存: {nc_memory}KB\n")
            file.write(f"qsrc结果:\n  时间: {rc_time:.6f}s, 内存: {rc_memory}KB\n")
            file.write(f"msnp结果:\n  时间: {np_time:.6f}s, 内存: {np_memory}KB\n")
            file.write(f"mspr结果:\n  时间: {pr_time:.6f}s, 内存: {pr_memory}KB\n")
            
            nc_times.append(nc_time)
            rc_times.append(rc_time)
            np_times.append(np_time)
            pr_times.append(pr_time)
            nc_memories.append(nc_memory)
            rc_memories.append(rc_memory)
            np_memories.append(np_memory)
            pr_memories.append(pr_memory)
        
        nc_avg_time=statistics.mean(nc_times)
        rc_avg_time=statistics.mean(rc_times)
        np_avg_time=statistics.mean(np_times)
        pr_avg_time=statistics.mean(pr_times)

        nc_avg_memory=statistics.mean(nc_memories)
        rc_avg_memory=statistics.mean(rc_memories)
        np_avg_memory=statistics.mean(np_memories)
        pr_avg_memory=statistics.mean(pr_memories)

        nc_var_time=statistics.variance(nc_times)
        rc_var_time=statistics.variance(rc_times)
        np_var_time=statistics.variance(np_times)
        pr_var_time=statistics.variance(pr_times)

        file.write("\n===========运行结果对比===========\n")
        file.write("      |  平均运行时间  |  平均运行空间  |  运行时间方差  \n")
        file.write("--------------------------------------------------\n")
        file.write(f"qsrc  | {rc_avg_time:12.6f} | {rc_avg_memory:12.0f} | {rc_var_time:12.6f}\n")
        file.write("--------------------------------------------------\n")
        file.write(f"qsnc  | {nc_avg_time:12.6f} | {nc_avg_memory:12.0f} | {nc_var_time:12.6f}\n")
        file.write("--------------------------------------------------\n")
        file.write(f"msnp  | {np_avg_time:12.6f} | {np_avg_memory:12.0f} | {np_var_time:12.6f}\n")
        file.write("--------------------------------------------------\n")
        file.write(f"mspr  | {pr_avg_time:12.6f} | {pr_avg_memory:12.0f} | {pr_var_time:12.6f}\n")
        
        A,B=op.curve_fit(f_1,ns,rc_times)[0]
        file.write(f"快速排序（递归式）数据量-时间拟合函数：{A:.5} x*log_2(x)+ {B:.5}\n")
        plt.scatter(ns,rc_times,s=1,alpha=0.25,color='red')
        x=np.arange(min(ns),max(ns),1)
        y=f_1(x,A,B)
        plt.plot(x,y,color='red',label='n-t_function_of_quick_sort_recurision')
        # plt.savefig("n-time_rc.svg",dpi=1200,format="svg")

        A,B=op.curve_fit(f_1,ns,nc_times)[0]
        file.write(f"快速排序（非递归）数据量-时间拟合函数：{A:.5} x*log_2(x)+ {B:.5}\n")
        plt.scatter(ns, nc_times,s=1,alpha=0.25,color='blue')
        x=np.arange(min(ns),max(ns),1)
        y=f_1(x,A,B)
        plt.plot(x,y,color='blue',label='n-t_function_of_quick_sort_not_recurision')
        # plt.savefig("n-time_nc.svg", dpi=1200,format="svg")

        A,B=op.curve_fit(f_1,ns,np_times)[0]
        file.write(f"归并排序（非并行）数据量-时间拟合函数：{A:.5} x*log_2(x)+ {B:.5}\n")
        plt.scatter(ns, np_times,s=1,alpha=0.25,color='black')
        x=np.arange(min(ns),max(ns),1)
        y=f_1(x,A,B)
        plt.plot(x,y,color='black',label='n-t_function_of_merge_sort_not_parallel')

        A,B=op.curve_fit(f_1,ns,pr_times)[0]
        file.write(f"归并排序（并行化）数据量-时间拟合函数：{A:.5} x*log_2(x)+ {B:.5}\n")
        plt.scatter(ns, pr_times,s=1,alpha=0.25,color='yellow')
        x=np.arange(min(ns),max(ns),1)
        y=f_1(x,A,B)
        plt.plot(x,y,color='yellow',label='n-t_function_of_merge_sort_parallel')

        plt.xlabel('datasize(*1e6)')
        plt.ylabel('runtime(/s)')

        plt.legend(loc="upper left")
        plt.savefig("n-time(default)(int).svg", dpi=2400,format="svg")
         
        plt.close()

        x=np.array(["qsrc","qsnc","msnp","mspr"])  
        y=np.array([rc_avg_time,nc_avg_time,np_avg_time,pr_avg_time])  
        plt.bar(x,y)
        plt.savefig("alo-avetime_bar(default)(int).svg",dpi=2400,format="svg")

def f_1(x,A,B):
    return A*x*np.log2(x)+B

def get_memory_usage():
    try:
        # 使用ps命令获取RSS内存(AI)
        result=subprocess.run(["ps", "-o", "rss=", "-p", str(os.getpid())],capture_output=True, text=True, check=True)
        return int(result.stdout.strip())
    except:
        return 0

if __name__ == "__main__":
    main()