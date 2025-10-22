# NCUSCC考核个人实验报告

## 创作者：南昌大学软件工程2510班游理皓

### 1.安装虚拟机：
我暑假在家就把老笔记本上的NOI_Linux虚拟机环境拷贝了过来，电脑上也安装有WSL，但是考虑到考核要求的环境设置以及日后学习工作所需的环境，与NOI_Linux的环境是不一样的，比如NOI_Linux不能联网下载C++插件只能通过终端手动输入指令进行编译运行；同时拷贝的VMware Station版本已经落后数年。以上情况对于本次考核，显然是不太能接受的。所以我决定重新安装虚拟机。

我按照高中收藏的[2021版 VMware虚拟机安装NOI Linux 2.0保姆级安装教程](https://zhuanlan.zhihu.com/p/412537240)进行安装，但是发现整个broadcom上似乎已经找不到“VMware Station Player”了，搜索之后才知道这玩意在去年年底已经彻底免费，我于是在免费产品里知道并下载了VMware Station Pro。下载的过程中我发现速度很慢，只有$ 700 \sim 900KB/s $ 左右，决定使用科学上网的方式，果然下载速度快了大概5倍。下载之后就是安装，由于时代变了，我决定找新的教程进行安装，我找到了一份今年9月刚刚更新的教程：[安装虚拟机（VMware）保姆级教程（附安装包）](https://blog.csdn.net/weixin_74195551/article/details/127288338)，并按照上面的方法逐步设置。

接着按照老教程把NOI_Linux的环境安装好之后，又按照新教程下载了ubuntu-24.04.3-desktop-amd64.iso源，并设置好了虚拟机。因为是按照教程装的，感觉好像我想说的也都在教程里了。

----------------------------------------------------------------------------------

### 2.安装 C 语言编译器：

接下来，我从VS Code的官网上下载了deb安装包，使用指令`sudo dpkg -i code_1.105.0-xxx_amd64.deb `安装了VS Code，由于Ubuntu的源是携带了gcc编译器，所以我并不需要下载gcc，而是按照以下顺序在终端输入：
``` bash
gcc -v
sudo apt update
sudo apt-get install build-essential gdb
mkdir project && cd project
mkdir helloworld && cd helloworld
code .
```
然后用VSC的终端里的生成运行文件自动创建了`task.json`文件，完成了基础默认环境的设置与搭建。

最后用经典的`helloworld.cpp`进行编译运行，发现正常编译运行输出了`Hello,World!`，确认了环境的正常与成功。

-------------------------------------------------

### 3.实现排序算法：

#### a.使用 C 语言手动实现快速排序算法（递归式）

~~因为我原本就会快排，所以这里就没有学习过程了。~~

快速排序的工作原理是通过分治的方式来将一个数组排序。C++里的`sort()`函数就是基于快速排序改进的内省排序。

快速排序分为三个过程：

- 将数列划分为两部分（要求保证相对大小关系）；
- 递归到两个子序列中分别进行快速排序；
- 不用合并，直接拼接，因为此时数列已经完全有序。

和归并排序不同，第一步并不是直接分成前后两个序列，而是在分的过程中要保证相对大小关系。具体来说，第一步要是要把数列分成两个部分，然后保证前一个子数列中的数都小于后一个子数列中的数。为了保证平均时间复杂度，一般是随机选择一个 $pivot$ 作为基准数来当做两个子数列的分界。

之后，维护一前一后两个指针 $p$ 和 $q$，依次考虑当前的数是否放在了应该放的位置（前还是后）。如果当前的数没放对，比如说如果后面的指针 $q$ 遇到了一个比 $pivot$ 小的数，那么可以交换 $p$ 和 $q$ 位置上的数，再把 $p$ 向后移一位。当前的数的位置全放对后，再移动指针继续处理，直到两个指针相遇。其实，快速排序没有指定应如何具体实现第一步，不论是选择 $pivot$ 的过程还是划分的过程，都有不止一种实现方法。

第三步中的序列已经分别有序且第一个序列中的数都小于第二个序列的第一个数，所以直接拼接起来就好了。

不过在实践的过程中，我们每次选择的基准数，也就是 $pivot$，如果每次都用数列的第一个数或者最后一个数作为它，虽然实现是很简单了，但是也存在致命的缺点：对已经有序或基本有序的数组，会导致极不平衡的划分，使算法的时间复杂度退化到 $O(n²)$。例如，对 $[1, 2, 3, 4, 5]$ 选择第一个元素 $1$ 作为基准，每次划分后，左子数组为空，右子数组只减少一个元素。如此递归下去，总共要递归 $n$ 层，而每层的数据量是 $n-depth$，根据等差数列求和，交换次数达到了惊人的 $\frac{n^2}{2}$，时间复杂度就是 $O(n^2)$。

我们不得不考虑优化 $pivot$ 的选择，不难想到，随机选择一个数组里的数字作为 $pivot$ 会是最优的。由于其随机性，$hacker$ 无法预测并构造一个数列 $hack$ 你，能够从根本上把这种退化的可能性降到接近0，时间复杂度稳定在 $O(n\log_2n) $，但是这会导致我们需要进行相同次数的随机生成，而随机数的生成是比较慢的，这导致我们的程序带上比其他方法要大一些的常数。

因此，我们在日常学习中可以选择三数取中，即取出待排序数组的首、中、尾三个元素，找出这三个元素的中位数，将其作为基准数。他的有点是无需随机数生成，避免了生成随机数造成的常数增加，性能稳定的同时，开销也小。同时还能有效避免对已排序数组、反向排序数组、全相等数组等常见特殊情况产生最坏性能。其缺点也很明显，因为是确定性算法，对于某些精心构造的数据，仍然可能被针对导致性能退化，不过比固定选择还是安全得多。因为此次考核的数据都是随机化生成，其退化的可能性相当小，且考核要比较算法性能，因此我选择这种方法。

我们进一步优化，在每次划分时，将与 $pivot$ 相等的元素保留下来，不参与左右分治，这样可以避免序列中大部分元素都相等的情况带来的退化。而这就是三路快速排序，它是快速排序和基数排序的有机结合，它的算法思想基于荷兰国旗问题的解法。与原始的快速排序不同，三路快速排序在选取 $pivot$ 后，将待排数列划分为三个部分：小于 $pivot$、等于 $pivot$ 以及大于 $pivot$。这使得它在处理元素大量重复的数组时，效率远高于原始快速排序。其最佳时间复杂度甚至能够达到 $O(n)$ （即所有元素的取值只有几个的情况）。

这样就可以开始写代码了，但是在实现中的过程会发现，C语言作为比C++低级一些的语言，是没有`swap()`、`max()`和`min()`等库函数，因此需要我们需要自行写好这些函数。

这里还要补充一下怎么取中位数，其实取中位数可以用总和减去最大值和最小值，~~但是这样太快了~~，所以我们可以只用最大值和最小值函数实现，$中位数=\max(\min(arr[l],arr[mid]),\min(\max(arr[l],arr[mid]),arr[r]))$，具体的代码如下，这只是整数排序的部分，浮点数改变一下数据类型即可。

```cpp line-numbers
void swapi(int* pa,int* pb){
    int temp=*pa;
    *pa=*pb;
    *pb=temp;
}
int maxi(int pa,int pb){
    if(pa>pb){
        return pa;
    }
    return pb;
}
int mini(int pa,int pb){
    if(pa>pb){
        return pb;
    }
    return pa;
}
void qsint(int a[],int len){
    if(len<=1){
        return;
    }
    int pivot=maxi(mini(a[0],a[(len-1)/2]),mini(maxi(a[0],a[(len-1)/2]),a[len-1]));
    int i=0,j=0,k=len;
    while(i<k){
        if(a[i]<pivot){
            swapi(&a[i++],&a[j++]);
        }
        else if(pivot<a[i]){
            swapi(&a[i],&a[--k]);
        }
        else{
            ++i;
        }
    }
    qsint(a,j);
    qsint(a+k,len-k);
}
```

#### b.使用 C 语言手动实现快速排序算法（非递归）

快排是一种分治算法，分治不可避免地要进行递归，但是递归会调用系统栈，有着一定的调用开销，如果非要减去这部分开销，我们就只能像系统一样使用栈来手动模拟递归过程。我们可以使用一个动态数组（或链表）作为栈，但是同样会有动态开销，所以这里用一个足够大的数组来模拟栈就差不多得了。我们首先初始化一个栈，将整个数组的起始和结束索引压入栈。然后循环以下步骤直到栈为空：
- a. 从栈中弹出一个子数组的起始和结束索引。
- b. 如果该子数组的长度小于等于1，则跳过。
- c. 否则，对该子数组进行划分，得到 $pivot$ 的位置。
- d. 将 $pivot$ 左边的子数组和右边的子数组的索引压入栈。

具体代码如下：

```cpp line-numbers
int sint(int* arr,int l,int r){
    int i=l,j=r,tmp=maxi(mini(arr[l],arr[(l+r)/2]),mini(maxi(arr[l],arr[(l+r)/2]),arr[r]));
    while (i!=j){
        while(tmp<=arr[j]&&i<j){
            j--;
        }
        while(tmp>=arr[i]&&i<j){
            i++;
        }
        if(i<j){ // i与j都停止移动时，交换数字
           int t=arr[i];
           arr[i]=arr[j];
           arr[j]=t;
        }
    }
    // i与j相遇，交换数字
    arr[l]=arr[i];
    arr[i]=tmp;
    return i;// 返回交汇点
}
void qsint(int* arr,int l,int r) {
    int *stack=(int *)malloc(sizeof(int)*r);
    for(int i=0;i<r;i++){
        stack[i]=-1;
    }
    int cnt=0;
    if(l<r){
        stack[cnt++]=l;
        stack[cnt++]=r;
    }
    while(cnt){ // 当栈非空时
        // 出栈操作
        int r_pop=stack[cnt-1],l_pop=stack[cnt-2];
        stack[cnt-1]=stack[cnt-2]=-1;// 出栈后，清空已出栈数据
        cnt-=2;
        int i=sint(arr,l_pop,r_pop);
        // 如果交汇点前面数据的下标比当前最左边的数据下标大，入栈
        if(l_pop<i-1){
            stack[cnt++]=l_pop;
            stack[cnt++]=i-1;
        }
        // 如果交汇点后面一个数据的下标比当前最右边数据的下标小，入栈
        if(r_pop>i+1){
            stack[cnt++]=i+1;
            stack[cnt++]=r_pop;
        }
    }
    free(stack);
    stack=NULL;
}
```

#### c.使用 C 语言手动实现归并排序算法（非并行）

归并排序的思想非常简单，就是对数组不断二分。

-  a.先二分下去直到区间长度为 $1$，。
-  b.二分完再合并左右两个子数组，此时左右的子数组都是有序的了。我们使用两个指针 $l$ 和 $r$，分别对应左右子数组的第一个也是最小的元素，每次比较指针指向的两个分别在左右子数组的元素，小的那边先合并进去，那组的指针也同时后移一位。
-  c.指针一直后移，直至两个指针全部指向各自子数组的最后一位。此时，子数组里的所有元素就全部被有序地合并了。

嗯，听上去就非常简单，实际上实现也非常简单。如果没有强制要求搞非递归的版本，递归式的归并排序只需要两个数组就行了。

```cpp line-numbers
void mergeint(int a[],int alen,int b[],int blen,int tmp[]){
    int i=0,j=0,k=0;
    while (i<alen&&j<blen){
        if(b[j]<a[i]){
            tmp[k]=b[j];
            ++j;
        }
        else{
            tmp[k]=a[i];
            ++i;
        }
        ++k;
    }
    for(int x=i;x<alen;++x,++k){
        tmp[k]=a[x];
    }
    for(int x=j;x<blen;++x,++k){
        tmp[k]=b[x];
    }
}
void msint(int arr[],int len,int tmp[]){
    if(len<=1){
        return;
    }
    int mid=len/2;
    msint(arr,mid,tmp);
    msint(arr+mid,len-mid,tmp+mid);
    int i=0,j=mid;
    mergeint(arr,mid,arr+mid,len-mid,tmp);
    for(int i=0;i<len;i++){
        arr[i]=tmp[i];
    }
}
```
#### d.使用 C 语言手动实现归并排序算法（并行化）

对上面的代码进行并行化，对于我这种小白非常困难，要利用OpenMP开启并行化，首先需要引入`<omp>`库头文件，在编译的时候还需要加上`-fopenmp` 的编译指令。OpenMP常见的并行化语句里，这这里能派上用场的有并行化普通for循环的`#pragma omp parallel for`、专长递归函数的`#pragma omp task`和直接分配线程的`#pragma omp parallel sections`。这三个语句均可后接`num_threads(n)`子句，表示为该并行化区域分配 $n$ 个线程。也可以在前面直接写`omp_set_num_threads(n);`，这两个写法是等效的。

- `#pragma omp parallel for`后接`schedule()`子句用于选择分配策略，其取值有：`static`表示静态分配策略，将for循环均匀切割并分配到 $n$ 个线程，每个线程被分配到的任务数量都是 $\frac{t}{n}$，其中，$t$ 是循环总次数。`dynamic`表示动态分配策略，即先完成当前计算的线程先被分配到新任务。

- `#pragma omp parallel sections`，下接`#pragma omp parallel section{}`表示将括号内的所有代码交给一个线程运行，默认情况下在最后一个`section`后面，会设置有一个等待点，先运行完的线程在运行完之后就会在此等待点等待，直到所有线程都运行完，再继续执行接下来的代码

- `#pragma omp task`是OpenMP比较常用的任务分配语句。我在我搜到的基础教程上并没有看到它，而是Deepseek告诉我还有这么一个语句的。使用它，首先需要使用
>```cpp line-numbers
>#pragma omp parallel
>{
>     #pragma omp single
>     msint(arr,len,tmp,0);
>}
>```
对函数进行封装才能有效使用，此外因为我们的任务是递归函数，所以还需要使用 `shared()` 与 `firstprivate()` 两个子句进一步声明，其中`shared()`表示需要进行任务间共享的变量，任务互相之间都能看见任何一个任务对变量产生的改变；而`firstprivate()`则提供了私有化的变量，避免了数据竞争，但每个任务只能看到自己的副本，不会看到其他任务的修改。

比较关键的是我们应该如何使用，我第一步试图优化我的for循环，比如输入输出，然而这效果并不明显，我询问Deepseek后得知，并行化操作对于文件输入输出的效果并不明显，反而会额外增加一定的开销，所以我们抛弃这个想法。

进一步，我想把合并的过程，从一个while循环＋两个for循环，也改写成一个一整个for循环，然鹅，当我改写完之后使用并行化时，编译失败了。

```bash
Starting build...
/usr/bin/gcc -fopenmp -fdiagnostics-color=always -g -Wl,-z,stack-size=8388608 -O1 -Wno-unused-result /home/youlhsj19/project/NCUSCC/mspr.c -o /home/youlhsj19/project/NCUSCC/mspr
/home/youlhsj19/project/NCUSCC/mspr.c: In function ‘mergeint’:
/home/youlhsj19/project/NCUSCC/mspr.c:7:25: error: expected iteration declaration or initialization before ‘i’
    7 |     for(int i=0,j=0,k=0;i<alen||j<alen;++k){
      |                         ^
/home/youlhsj19/project/NCUSCC/mspr.c: In function ‘mergefloat’:
/home/youlhsj19/project/NCUSCC/mspr.c:52:25: error: expected iteration declaration or initialization before ‘i’
   52 |     for(int i=0,j=0,k=0;i<alen||j<alen;++k){
      |                         ^

Build finished with error(s).
```
欸，为什么呢？这个错误是因为在OpenMP中，`#pragma omp parallel for`要求循环必须是一个规范的循环，即：for (初始化; 条件; 递增)

其中，初始化部分只能初始化一个循环变量（或者多个，但必须用逗号分隔，且第一个必须是循环变量），并且循环变量必须是整数类型。条件部分必须只使用循环变量，递增部分必须是对循环变量的递增。

我们的循环中使用了三个变量 $i$,$j$,$k$，并且条件部分使用了 $i$ 和 $j$，这不符合OpenMP循环的要求。

人话说就是，条件太复杂了，$i$ 和 $j$ 都不是在递增里变化的，而是取决与之前的循环步骤，并行化之后的任务互相之间是互相影响的，没办法并行化。

对于合并两个有序数组，传统的合并算法是顺序的，很难并行化。但是我们可以先确定每个元素在什么位置，在合并，但是我们为什么要多此一举呢？我们在确定位置的时候明明可以直接合并放进去的，这会增加我们的计算量，使得常数接近翻倍，舍弃。

那么我继续思考如何将递归任务进行并行化，`#pragma omp parallel sections`语法简单，我直接使用它把左边的递归交给一个线程做，右边的交给另一个线程做不是很简单很快吗？

事实上又错了，经过性能测试，我们的代码并没有明显优化，这是何意味？

我调用`omp_get_num_thread()`查看我的递归都分配到了哪些线程，好家伙，不看不知道，一看吓一跳，我的所有的递归自始至终只用三个线程在跑，同时for循环也只有两个线程在跑。何意味？

询问Deepseek，这才知道，在递归过程中，每次进入递归都会创建新的`section`，但每次只有两个线程被使用，所以在递归树中只有部分线程被使用。而且OpenMP的默认限制限制了递归并行化的继续，OpenMP默认情况下在并行区域是不能继续新开并行区域的，即禁用**嵌套并行**，所以，自始至终只有深度为0的一个和速度为1两个递归函数在并行化运行。

我问到了解除限制的代码，但是加上去运行时间就爆炸了，甚至比普通快排慢了两个数量级，何意味？

原来是递归太深，创建的线程太多，开销太大，反而负优化了。

限制递归深度在4之内之后还是非常慢，我询问Deepseek建议我使用`#pragma omp task`，使用OpenMP的`task`构造来替代`sections`。`task`可以动态地生成任务，自动利用所有可用线程，并由线程池中的线程动态窃取任务，从而更好地实现负载均衡。同时还要在并行区域内部使用single构造来创建任务，确保任务只被创建一次。

改完之后优化效果非常明显，这点我们将在后面的数据分析里谈到，下面是主要代码：
 
```cpp line-numbers
void mergeint(int a[],int alen,int b[],int blen,int tmp[]){
    int i=0,j=0,k=0;
    while (i<alen&&j<blen){
        if(b[j]<a[i]){
            tmp[k]=b[j];
            ++j;
        }
        else{
            tmp[k]=a[i];
            ++i;
        }
        ++k;
    }
    for(int x=i;x<alen;++x,++k){
        tmp[k]=a[x];
    }
    for(int x=j;x<blen;++x,++k){
        tmp[k]=b[x];
    }
}
void msint(int arr[],int len,int tmp[],int dep){
    if(len<=1){
        return;
    }
    int mid=len/2;
    if(dep<3){
        #pragma omp task shared(arr,tmp) firstprivate(mid,dep)
        {
            msint(arr, mid, tmp, dep + 1);
        }
        #pragma omp task shared(arr,tmp) firstprivate(mid,len,dep)
        {
            msint(arr + mid, len - mid, tmp + mid, dep + 1);
        }
        #pragma omp taskwait
        int i=0,j=mid;
        mergeint(arr,mid,arr+mid,len-mid,tmp);
        for(int i=0;i<len;i++){
            arr[i]=tmp[i];
        }
    }
    else{
        msint(arr,mid,tmp,dep+1);
        msint(arr+mid,len-mid,tmp+mid,dep+1);
        int i=0,j=mid;
        mergeint(arr,mid,arr+mid,len-mid,tmp);
        for(int i=0;i<len;i++){
            arr[i]=tmp[i];
        }
    }
}
void parallel_msint(int arr[],int len,int tmp[]) {
    #pragma omp parallel
    {
        #pragma omp single
        msint(arr,len,tmp,0);
    }
}
```

### e.编写测试代码

太简单了，首先根据第一个参数判断是整形还是浮点型，第二个参数表示数据量，接下来输入数组，因为我们正确的情况下数据是从小到大的排好了序的，只需要判断是否有 $arr[i-1]>arr[i]$ 的存在即可。

经过验证，值得注意的是传参数的时候要注意我们的数组是从 $arr[0]$ 开始储存的还是从 $arr[1]$。我的快速排序因为主函数从 $arr[1]$ 开始，子函数却是从 $arr[0]$ 开始的，最后一个数没有被排序。最后改完，已经没有其他问题了。

---

### 4.生成测试数据：

首先，编写数据生成器，$flag$表示我们的数据类型，$n$ 表示待排序的元素个数。我们的 $n$ 需要随机分布，这样才能统计运行时间随数据量的增加的变化情况。

我们考虑使用`mt19937`种子，这是一个在OI竞赛中常用比较强的随机数生成种子，然而在实际运行中，我发现大概每$10$组测试数据，其数据量是一样的，这是由于程序运行时间太短，所以在短时间内，依赖时钟产生随机数就会出现重复。经过搜索，终于找到了随机性更强的方法：直接利用电脑系统的熵池产生随机数，这种方法产生的随机数不依赖时间，而是硬件系统，每次生成的随机数都几乎是完全随机的，这样一来，我们的数据的随机性得到了保证。但是这种方法也有弊端，熵池是硬件系统重要的组成部分，如果短时间大量生成随机数就会耗尽，熵池耗尽将使得设备性能急剧下降。在实践中，我发现这确实是存在的，在最后的几组测试中，排序的速度下降了超过十倍，所以我决定只利用**熵池**生成数据量，也就是 $n$，而待排序的数据依然使用`mt19937`作为种子进行生成，这样既保证了数据量在 $1～1e6$ 中间的随机分布，也兼顾了降低测试耗时与保障设备性能。

整个数据的传递过程使用文件输入输出，`datarequirement.txt`负责保存五个数据控制变量，分别是 $flag$、$nlim_l$、$nlim_r$、$l$和$r$，分别表示数据类型，数据量的上下界以及元素的上下界。`dataproducer.c`读入`datarequirement.txt`并生成数据保存在`testdata.txt`中，而`qsrc.c`、`quick.c`、`msnp.c`、`mspr.c`则依次读入数据并排序，将结果保存在`results(xxxx).txt`中，在用`checker(xxxx).c`分别读入进行结果检查，如果四个排序程序结果全部正确，再将测试所花费的时间空间等数据保存在`testdetail()().txt`中，两个括号分别用来标注测试的条件，这在后面会具体讲述。

一个完整的测试流程将随机生成1000组数据量在1～1e6之间随机分布的测试数据并进行测试，使得数据结构具有足够的分布密度体现运行时间随数据量的变化，同时兼顾测试效率，整型数据能够在10分钟左右完成测试，这是相当惊人的测试效率。

---

### 5.编译与性能测试：

为了快速完成测试，我直接通过改变`task.json`控制编译选项，在`avg`中添加`'-O2'`,即可自动在编译时开启O2优化。因此，我在一次测试中，只需要先修改`datarequirement.txt`，再修改`task.json`，接着把四个排序代码重新编译生成可执行文件，最后启动`run.py`等待测试完成即可。也许这套流程还是比较麻烦，但是对于我来说还是挺便捷了。

我通过Python的`time`包记录程序运行时间，在某个排序代码运行前后分别用`time.time()`记录时间，直接相减就得到了运行时间。其实在C里也有对应的类似的库头文件，直接在主函数的头尾记录时间会更加准确，但是因为是在全部代码都已经写好之后才得知，要再更改就很麻烦了，遂作罢。

---

### 6.数据记录与可视化：

运行完排序代码后利用Python的`matplotlib`和`math`包进行统计，首先用`plt.scatter()`依次描绘每组测试数据下某程序运行时间的n-time散点图。再利用op.curve_fit()和`y=f_1(x,A,B)`和`plt.plot()`，对某个排序算法的n-time散点图进行拟合并绘制在散点图上，拟合的回归方程是 $time=A\times n \log_2n + B$。最后将散点图保存在`n-time(O0)(int).svg`中，表示在O0编译环境下，测试数据均为int型的测试结果。

我还利用`plt.bar()`统计了各个算法的平均时间的柱状图，保存为`alo-avetime_bar(xxx)(xxx).svg`。我还将每一组数据具体的运行时间和占用空间、平均运行时间、平均占用空间、运行时间的回归相关系数（反映算法的稳定性），通过文字表格的形式保存在了`testdetail(xxx)(xxx).txt`中，防止具体数据的丢失。

我分整型和浮点型，依次在 `-O0, -O1, -O2, -O3, -Ofast`的情况下进行测试。

测试的图像结果如下：

这是n-time(default)(int)：
![n-time(default)(int).png](https://youke1.picui.cn/s1/2025/10/22/68f8eef8bfc8a.png)

这是n-time(default)(float)：
![n-time(default)(float).png](https://youke1.picui.cn/s1/2025/10/22/68f8eef85c415.png)

这是n-time(O0)(int)：
![n-time(O0)(int).png](https://youke1.picui.cn/s1/2025/10/22/68f8eee8d8514.png)

这是n-time(O0)(float)：
![n-time(O0)(float).png](https://youke1.picui.cn/s1/2025/10/22/68f8eee891e2b.png)

这是n-time(O1)(int)：
![](https://youke1.picui.cn/s1/2025/10/22/68f8eee9621c6.png)

这是n-time(O1)(float)：
![n-time(O1)(float).png](https://youke1.picui.cn/s1/2025/10/22/68f8eee975dfd.png)

这是n-time(O2)(int)：
![](https://youke1.picui.cn/s1/2025/10/22/68f8eef085ee4.png)

这是n-time(O2)(float)：
![n-time(O2)(float).png](https://youke1.picui.cn/s1/2025/10/22/68f8eee967b28.png)

这是n-time(O3)(int)：
![n-time(O3)(int).png](https://youke1.picui.cn/s1/2025/10/22/68f8eef09ce90.png)

这是n-time(O3)(float)：
![](https://youke1.picui.cn/s1/2025/10/22/68f8eef1251bc.png)

这是n-time(Ofast)(int)：
![n-time(Ofast)(int).png](https://youke1.picui.cn/s1/2025/10/22/68f8eef6d8fb4.png)

这是n-time(Ofast)(float)：
![n-time(Ofast)(float).png](https://youke1.picui.cn/s1/2025/10/22/68f8eef235113.png)

#### 时间复杂度分析

快速排序的最优时间复杂度和平均时间复杂度为 $O(n\log n)$，最坏时间复杂度为 $O(n^2)$。

对于最优情况，每一次选择的分界值都是序列的中位数，此时算法时间复杂度满足的递推式为 $T(n) = 2T(\dfrac{n}{2}) + \Theta(n)$，由主定理，$T(n) = \Theta(n\log n)$。

对于最坏情况，每一次选择的分界值都是序列的最值，此时算法时间复杂度满足的递推式为 $T(n) = T(n - 1) + \Theta(n)$，累加可得 $T(n) = \Theta(n^2)$。

而我们使用三数取中和三路排序在很大程度上避免了最坏情况的发生，再加上随机生成的数据，使得我们的代码可以看成就是 $O(n\log n)$。

对于归并排序，一个本质上是二分的算法的时间复杂度毫无疑问是稳定的 $O(n \log n)$，归并排序总共的递归速度是 $\log n$，而我们每个元素在二分完后会被合并进入数组一次，故而时间复杂度就是 $O(n \log n)$ 的。

#### 数据分析

根据图中的数据，我们可以分析出：

1. 数据类型影响显著：整数排序明显快于浮点数，在所有优化级别下，`int`类型的排序时间都明显短于`double`类型，大约只有浮点数的一半时间。可能的原因：整数运算通常比浮点数运算更快，比较和交换操作更高效。

2. 编译优化效果明显：O0 → O1/O2，性能提升显著。O2/O3/Ofast，优化效果趋于稳定，提升幅度减小。O2在某些`double`情况下出现性能回退：可能由于激进优化导致缓存或分支预测问题。

3. 数据量越大，并行化的优势越大：在整型数据的情况下，无论是什么优化条件下，并行化的归并排序都会在数据量为 $2e5~4e5$ 时，运行速度超过其他所有算法，当数据量达到 $1e6$ 时，普遍比非并行化归并排序快接近 $0.05s$。

4. 数据类型对并行化的优势有严重干扰：可以看到，当数据为浮点数时，并行化快排的优势并不明显，当数据量达到 $1e6$ 时，不仅比非递归的快速排序慢约 $0.075s$，还只比其他两种有着微不足道的加速。分析可能的原因：当数据为浮点数时，增加的绝大多数开销，在为浮点数进行比较与交换赋值，而非递归快速排序大量栈操作使用下标指针代替原元素，而这些指针都是`int`类型，大大减少了所需的时间开销，而这里我的并行化操作主要是对递归过程进行并行化，没有使得浮点数类型的操作得到优化，故而优化效果不明显。

#### 可能对并行化的改进措施

类似非递归化，将原元素使用下标代替进行比对与交换，最后按照指针顺序对于原数组即可。使用`#pragma omp for`加速for循环。
