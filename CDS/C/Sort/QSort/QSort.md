# QSort算法实现

<!-- vim-markdown-toc GFM -->

* [算法思路](#算法思路)
	* [通过基元划分无序组](#通过基元划分无序组)
* [算法的实现方法](#算法的实现方法)
	* [选基元](#选基元)
	* [划分](#划分)
	* [递归执行](#递归执行)

<!-- vim-markdown-toc -->

## 算法思路

### 通过基元划分无序组
最开始我们处理的是一个无序组，而QSort算法的第一步，就是从无序组中选出一个基元***[P1]***
，划分后，我们就得到的两个新的无序组B与C。接下来我们至需要再对B与C重复以上两个步骤
（选基元，划分),最后直到被划分的组长度为1时，便可停止，因为，最小的有序组长度是1，反之
亦然。

>P1:基元是无序组中的一个元素，它的特殊之处在于我们将以它为标准将无序组A划分为两个无序组B与C
，其中要求B中的所有元素要小于基元a，而要求C中的元素要都大于基元a。

## 算法的实现方法

### 选基元
基元的选取方式有许多种，比如：选当前无序组中第一个元素作为基元，选当前无序组中中间元素
为基元的等等，而我在实现中选择将第一个元素作为基元（这样做的原因，我将在之后作出解释）。

### 划分
再完成第一步之后，我们就需要考虑如何划分当前无序组了。我所使用的划分方式是用循环从当前
无序组的第2个元素开始遍历（第一个被我选作基元）.每遍历一个元素b，就拿它与基元a进行大小
比较.  
若b大于或等于a:则遍历索引i++(这样做的原因是，在划分要求中，比基元大的元素属于无序
组C，因此无需做更多处理).  
若b小于a：则从遍历索引处的元素开始依次与前一个元素进行交换，直到与基元进行交换后停止。
***[P3]***

>P2;为什么选择第一个元素作为基元呢？因为在上述的划分算法中，我采取从左到右依次遍历的
方式来完成。如果，不选取第一个元素作为基元，那么我们还需要多一步基元与第一位元素的交换，
才能使用上述算法完成划分。  

>P3;为什么要这样做呢？根据我们划分的要求，比基元小的元素应该放在基元的左边，将这个元素与
基元交换位置就可以了吗？我们当然不能这样做，因为此时我们知道在基元与索引元素之间可能还存
在着一些比基元大的元素，这是由我们之前比较产生的结果，所以，我们该怎么做才能使索引元素位
于基元左边，同时不破坏它们之间比基元大的元素与基元之间的相对关系呢？我采取的方式就是将索
引元素与前一个元素进行交换，直到与基元发生交换后停止。  

### 递归执行
最后，我们只需要递归的执行第一步与第二步就可以了。  

*感谢阅读，文章如有错误，望指正，万分感谢*
