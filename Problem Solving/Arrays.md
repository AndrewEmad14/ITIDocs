Hashmap usage 
        hasmaps can be used to solved many problems that require you to keep track of freq

Encoding
        use the string to input useful data when converting

postfix and prefix

postfix is any operations or value after the current value
prefix is any operations or values before the current value

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int size=nums.size();
        vector<int> ans(size), postfix(size),prefix(size);
        prefix[0]=1;
        postfix[size-1]=1;
        for(int i=1;i<size;i++){
            prefix[i]=prefix[i-1]*nums[i-1];
        }
        for(int i=1;i<size;i++){
            postfix[size-i-1]=postfix[size-i]*nums[size-i];
        }
        for(int i=0;i<size;i++){
            ans[i]=prefix[i]*postfix[i];
        }
        return ans;
           
    }
};