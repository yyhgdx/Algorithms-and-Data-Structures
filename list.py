class Solution:
    def findMedianSortedArrays(self, nums1, nums2) -> float:
        a1 = len(nums1)
        a2 = len(nums2)
        a3 = 0
        if (a2 > a1):
            nums3 = nums1
            nums1 = nums2
            nums2 = nums3
            a3 = a1
            a1 = a2
            a2 = a3
        stop = 0
        exlude_item = (a1 - a2 - 1) // 2
        if (a2 != 0):
            if (exlude_item < 0): exlude_item = 0
            star1 = 0 + exlude_item
            end1 = a1 - 1 - exlude_item
            k1 = nums1[(star1 + end1) // 2]
            if (a1 > 1):
                k3 = nums1[(star1 + end1) // 2 + 1]
            else:
                k3 = k1
            star2 = 0
            end2 = a2 - 1
            k2 = nums2[(star2 + end2) // 2]
            a1 = a1 - exlude_item - exlude_item
            if (a2 > 1):
                k4 = nums2[(star2 + end2) // 2 + 1]
            else:
                k4 = k2
            if (a1 - a2 >= 2 or a1 - a2 == 1 or a1 == a2):
                while ((stop != 1 and stop != 2) and star2 != end2):
                    if (a1 % 2 == 0 and a2 % 2 == 0):
                        a1, a2, star1, end1, star2, end2, stop = self.compare2(a1, a2, star1, end1, star2, end2, k1, k2,
                                                                               k3, k4, stop)
                    else:
                        a1, a2, star1, end1, star2, end2, stop = self.compare1(a1, a2, star1, end1, star2, end2, k1, k2,
                                                                               stop)
                    k1 = nums1[(star1 + end1) // 2]
                    if (a1 > 1):
                        k3 = nums1[(star1 + end1) // 2 + 1]
                    k2 = nums2[(star2 + end2) // 2]
                    if (a2 > 1):
                        k4 = nums2[(star2 + end2) // 2 + 1]
            if (stop == 1):
                return k1
            elif (stop == 2):
                if (k1 >= k2 and k3 <= k4):
                    return (k1 + k3) / 2
                elif (k2 >= k1 and k4 <= k3):
                    return (k4 + k2) / 2
                elif (k2 >= k1 and k2 <= k3):
                    return (k3 + k2) / 2
                else:
                    return (k1 + k4) / 2
            else:
                if (end1 - star1 == 1):
                    if (k1 > k2):
                        return k1
                    elif (k1 < k2 and k3 >= k2):
                        return k2
                    else:
                        return k3
                elif (end1 - star1 == 2):
                    if (nums1[(star1 + end1) // 2 - 1] > k2):
                        return (k1 + nums1[(star1 + end1) // 2 - 1]) / 2
                    elif (nums1[(star1 + end1) // 2 + 1] < k2):
                        return (k1 + nums1[(star1 + end1) // 2 + 1]) / 2
                    else:
                        return (k1 + k2) / 2
                elif (end1 == star1):
                    return (k1 + k2) / 2
        else:
            if (exlude_item < 0): exlude_item = 0
            star1 = 0 + exlude_item
            end1 = a1 - 1 - exlude_item
            k1 = nums1[(star1 + end1) // 2]
            if (a1 > 1):
                k3 = nums1[(star1 + end1) // 2 + 1]
            if (a1 % 2 == 1):
                return k1
            else:
                return (k1 + k3) / 2

    def compare1(self, a1, a2, star1, end1, star2, end2, k1, k2, stop):
        if (a1 != a2):
            if (k1 > k2):
                if (a2 % 2 == 1):
                    star2 = (star2 + end2) // 2
                else:
                    star2 = (star2 + end2) // 2 + 1
                end1 = end1 - (a2 // 2)
                a1 = end1 - star1 + 1
                a2 = end2 - star2 + 1
                return a1, a2, star1, end1, star2, end2, stop
            elif (k1 < k2):
                if (a2 % 2 == 1):
                    star1 = star1 + a2 // 2
                    end2 = (star2 + end2) // 2
                else:
                    star1 = (star1 + end1) // 2
                    end2 = (star2 + end2) // 2
                a1 = end1 - star1 + 1
                a2 = end2 - star2 + 1
                return a1, a2, star1, end1, star2, end2, stop
            else:
                stop = 1
                return a1, a2, star1, end1, star2, end2, stop
        else:
            if (k1 > k2):
                star2 = (star2 + end2) // 2
                end1 = end1 - (a2 // 2)
                a1 = end1 - star1 + 1
                a2 = end2 - star2 + 1
                return a1, a2, star1, end1, star2, end2, stop
            elif (k1 < k2):
                star1 = (star1 + end1) // 2
                end2 = (star2 + end2) // 2
                a1 = end1 - star1 + 1
                a2 = end2 - star2 + 1
                return a1, a2, star1, end1, star2, end2, stop
            else:
                stop = 1
                return a1, a2, star1, end1, star2, end2, stop

    def compare2(self, a1, a2, star1, end1, star2, end2, k1, k2, k3, k4, stop):
        if (a1 != a2):
            if (k1 > k4):
                end1 = (star1 + end1) // 2 + 1
                star2 = (star2 + end2) // 2 + 1
                a1 = end1 - star1 + 1
                a2 = end2 - star2 + 1
                return a1, a2, star1, end1, star2, end2, stop
            elif (k2 > k3):
                star1 = (star1 + end1) // 2
                end2 = (star2 + end2) // 2
                a1 = end1 - star1 + 1
                a2 = end2 - star2 + 1
                return a1, a2, star1, end1, star2, end2, stop
            else:
                stop = 2
                return a1, a2, star1, end1, star2, end2, stop
        else:
            if (k1 > k4):
                end1 = (star1 + end1) // 2
                star2 = (star2 + end2) // 2 + 1
                a1 = end1 - star1 + 1
                a2 = end2 - star2 + 1
                return a1, a2, star1, end1, star2, end2, stop
            elif (k2 > k3):
                star1 = (star1 + end1) // 2 + 1
                end2 = (star2 + end2) // 2
                a1 = end1 - star1 + 1
                a2 = end2 - star2 + 1
                return a1, a2, star1, end1, star2, end2, stop
            else:
                stop = 2
                return a1, a2, star1, end1, star2, end2, stop
if __name__ == '__main__':
    list1=[1,2]
    list2=[5]
    a=Solution.findMedianSortedArrays(0,list1,list2)
    print(a)