//Abdul Shaqildi CS251 Summer 2021
#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class bst {

private:
    struct bst_node {
        T      val;
        bst_node* left;
        bst_node* right;
        bst_node* prev;
        int treeSize;
        int Lsize;
        int Rsize;
        bst_node(const T& _val = T{}, bst_node* l = nullptr, bst_node* r = nullptr, bst_node* _prev = nullptr, int _Tsize = 1, int _Rsize = 0, int _Lsize = 0)
            : val{ _val }, left{ l }, right{ r }, prev{ _prev }, treeSize{_Tsize}, Rsize{_Rsize}, Lsize{ _Lsize }
        { }
    };



public:
    // constructor:  initializes an empty tree
    bst() {
        root = nullptr;
    }

private:
    // helper function which recursively deallocates nodes
    //   in a tree.
    static void delete_nodes(bst_node* r) {
        if (r == nullptr) return;

        delete_nodes(r->left);
        delete_nodes(r->right);
        delete r;
    }

public:
    // destructor
    ~bst() {
        delete_nodes(root);
    }

private:

    /**
     * function:  insert()
     * desc:      recursive helper function inserting x into
     *            binary search tree rooted  at r.
     *
     * returns:   pointer to root of tree after insertion.
     *
     * notes:     if x is already in tree, no modifications are made.
     */
    static bst_node* _insert(vector<bst_node*>& V, bst_node* r, T& x, bool& success) {
        if (r == nullptr) {
            success = true;
            return new bst_node(x, nullptr, nullptr,nullptr);
        }

        

        if (r->val == x) {
            success = false;
            return r;
        }
        V.push_back(r);

        if (x < r->val) {
            r->left = _insert(V,r->left, x, success);
            r->Lsize = r->left->treeSize;
            r->left->prev = r;
            r->treeSize = r->Lsize+r->Rsize+ 1;
            return r;
        }
        else {
            r->right = _insert(V,r->right, x, success);
            r->Rsize = r->right->treeSize;
            r->right->prev = r;
            r->treeSize = r->Lsize + r->Rsize + 1;
            return r;
        }
    }


public:
    /**
     * function:  insert
     * desc:      inserts x into BST given by t.  Note that
     *            a BST stores a SET -- no duplicates.  Thus,
     *            if x is already in t when call made, no
     *            modifications to tree result.
     *
     * note:      helper function does most of the work.
     *
     */
    bool insert(T& x) {
        bool success;
        vector<bst_node*> vec;
        
        root = _insert(vec,root, x, success);
        int n = vec.size();
        if(success == true)
        {
            for (int i = n-1; i>=0; i--)
            {

                bst_node* r = vec[i];
                
               
                int Max = (r->Lsize < r->Rsize) ? r->Rsize : r->Lsize;
                int Min = 2 * (!(r->Rsize < r->Lsize) ? r->Lsize : r->Rsize) + 1;
                if (Max > Min)
                {
                   
                    bst_node* prev = r->prev;
                    r = SizeBal(r);
                    if(prev == nullptr)
                    {
                        root = r;
                        r->prev = nullptr;
                        break;
                    }
                    if (prev->val < r->val)
                    {
                        prev->right = r;
                        r->prev = prev;
                        break;
                    }
                    else {
                       prev->left = r;
                       r->prev = prev;
                        break;
                    }
                    
                }
            }
        }
        return success;
    }

    /**
     * function:  contains()
     * desc:      returns true or false depending on whether x is an
     *            element of BST (calling object)
     *
     */
    bool contains(const T& x) {
        bst_node* p = root;

        while (p != nullptr) {

            if (p->val == x)
                return true;
            if (x < p->val) {
                p = p->left;
            }
            else {
                p = p->right;
            }
        }
        return false;
    }
private:
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node* _min_node(bst_node* r) {
        if (r == nullptr)
            return nullptr; // should never happen!
        while (r->left != nullptr)
            r = r->left;
        return r;
    }
   
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node* _max_node(bst_node* r) {
        if (r == nullptr)
            return nullptr; // should never happen!
        while (r->right != nullptr)
            r = r->right;
        return r;
    }

    // recursive helper function for node removal
    //   returns root of resulting tree after removal.
    static bst_node* _remove(vector<bst_node*>& V, bst_node* r, T& x, bool& success) {
        bst_node* tmp;
        bool sanity;
        if (r == nullptr) {
            success = false;
            return nullptr;
        }
        
        if (r->val == x) {
            success = true;

            if (r->left == nullptr) {
                tmp = r->right;
                delete r;
                return tmp;
            }
            if (r->right == nullptr) {
                tmp = r->left;
                delete r;
                return tmp;
            }
            // if we get here, r has two children
           V.push_back(r);
            r->val = _min_node(r->right)->val;
            r->right = _remove(V,r->right, r->val, sanity);
            if (r->right != nullptr)
            {
                r->Rsize = r->right->treeSize;
            }
            else
            {
                r->Rsize = 0;
            }
            if (r->left != nullptr)
            {
                r->Lsize = r->left->treeSize;
            }
            else
            {
                r->Lsize = 0;
            }
            r->treeSize = r->Rsize + r->Lsize + 1;
            if (!sanity)
                std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
            return r;
        }
        V.push_back(r);
        if (x < r->val) {
            
            r->left = _remove(V,r->left, x, success);
        }
        else {
            r->right = _remove(V,r->right, x, success);
        }

        if (r->right != nullptr)
        {
            
            r->Rsize = r->right->treeSize;
        }
        else
        {
            r->Rsize = 0;
        }
        if (r->left != nullptr)
        {
            r->Lsize = r->left->treeSize;
        }
        else
        {
            r->Lsize = 0;
        }
        r->treeSize = r->Rsize + r->Lsize + 1;
        return r;

    }

public:

    bool remove(T& x) {
        bool success;
        vector<bst_node*> vec;
        
        root = _remove(vec,root, x, success);
        if (success == true)
        {
            
            int n = vec.size();
            for (int i = n -1; i >= 0; i--)
            {

                bst_node* r = vec[i];
             
               
                int Max = (r->Lsize < r->Rsize) ? r->Rsize : r->Lsize;
                int Min = 2 * (!(r->Rsize < r->Lsize) ? r->Lsize : r->Rsize) + 1;
                if (Max > Min)
                {
                 
                    bst_node* prev = r->prev;
                    r = SizeBal(r);
                    if (prev == nullptr)
                    {
                        root = r;
                        r->prev = nullptr;
                        break;
                    }
                    if (prev->val < r->val)
                    {
                        prev->right = r;
                        r->prev = prev;
                        break;
                    }
                    else {
                        prev->left = r;
                        r->prev = prev;
                        break;
                    }

                }
            }
        }
        
        return success;
    }


private:
    // recursive helper function to compute size of
    //   tree rooted at r
    static int _size(bst_node* r) {
        if (r == nullptr) return 0;
        return r->treeSize;
    }

public:
    int size() {
        return _size(root);
    }

private:

    static int _height(bst_node* r) {
        int l_h, r_h;

        if (r == nullptr) return -1;
        l_h = _height(r->left);
        r_h = _height(r->right);
        return 1 + (l_h > r_h ? l_h : r_h);
    }

public:

    int height() {
        return _height(root);
    }

    bool min(T& answer) {
        if (root == nullptr) {
            return false;
        }
        answer = _min_node(root)->val;
        return true;
    }

    T max() 
    {
        return _max_node(root)->val;
    }

    /******************************************
     *
     * "stubs" for assigned TODO functions below
     *
     *****************************************/

     /* TODO
      * Function:  to_vector
      * Description:  allocates a vector of type T and populates
      *               it with the elements of the tree in sorted
      *               order.  A pointer to the vector is returned.
      *
      * runtime:  O(n) where n is the tree size.
      *
      */
    
    std::vector<T>* to_vector() 
    {   
        if (root == nullptr) 
        {
            return nullptr;
        }
        vector<T>* vec = new vector<T>();
        vec->reserve(root->treeSize);
        _to_vector(root, vec);
        return vec;
    }
   
    /* TODO
     * Function:  get_ith
     * Description:  determines the ith smallest element in t and
     *    "passes it back" to the caller via the reference parameter x.
     *    i ranges from 1..n where n is the number of elements in the
     *    tree.
     *
     *    If i is outside this range, false is returned.
     *    Otherwise, true is returned (indicating "success").
     *
     * Runtime:  O(h) where h is the tree height
     */
    bool get_ith(int i, T& x)
    {
        int n = root->treeSize;
        if(i < 1 || n <i)
        {
            return false;
        }

        _get_ith(root, i, x);
        return true;

    }
    /*
     * get_ith_SLOW:  slow version of get_ith which gives the right answer, but
     *   does so by "walking the entire tree".
     * might be helpful for debugging?
     * Private helper below does most of the work
     */
    bool get_ith_SLOW(int i, T& x) {
        int n = size();
        int sofar = 0;

        if (i < 1 || i > n)
            return false;

        _get_ith_SLOW(root, i, x, sofar);
        return true;
    }

private:
    // DONE DELETE LATER recursive helper function that does most of the work
    static void _get_ith_SLOW(bst_node* t, int i, T& x, int& sofar) {
        if (t == nullptr)
            return;
        _get_ith_SLOW(t->left, i, x, sofar);

        if (sofar == i)
            return;
        sofar++;
        if (sofar == i) {
            x = t->val;
            return;
        }
        _get_ith_SLOW(t->right, i, x, sofar);
    }
  
    // recursive helper function MY WORK 
    static void _get_ith(bst_node* t, int i, T& x)
    {

        if (t == nullptr)
        {
            return;
        }
        int count = t->Lsize + 1;

        if (count == i)
        {
            x = t->val;
            return;
        }
        if (count > i)
        {
            _get_ith(t->left, i, x);
            return;
        }
        _get_ith(t->right, i - count, x);

    }

    static void _to_vector(bst_node* t, vector<T>* vec)
    {
        if (t == nullptr)
        {
            return;
        }

        _to_vector(t->left, vec);
        vec->push_back(t->val);
        _to_vector(t->right, vec);
    }
public:

    /* TODO
     * Function: position_of
     * Description:  this is like the inverse of
     *       get_ith:  given a value x, determine the
     *       position ("i") where x would appear in a
     *       sorted list of the elements and return
     *       the position as an integer.
     *       If x is not in the tree, -1 is returned.
     *       Examples:
     *           if x happens to be the minimum, 1 is returned
     *           if x happens to be the maximum, n is returned where
     *               n is the tree size.
     *
     *       Notice the following property:  for a bst t with n nodes,
     *           pick an integer pos:1 <= pos <= n.
     *           Now consider the following:
     *
                    T x;
                    int pos, pos2;
                    // set pos to a value in {1..n}
                    t.get_ith(pos, x);  // must return true since pos is in {1..n}

                    // now let's find the position of x (just retrieved)
                    pos2 = t.position_of(x);
                    if(pos != pos2) {
                        std::cout << "THERE MUST BE A BUG!\n";
                    }

                 See how position_of performs the inverse operation of get_ith?
     *
     * Return:  -1 if x is not in the tree; otherwise, returns the position where x
     *          would appear in the sorted sequence of the elements of the tree (a
     *          value in {1..n}
     *
     * Runtime:  O(h) where h is the tree height
     */
    int position_of(const T& x) 
    {
        int pos;
        int n = root->treeSize;
        pos = _position_of(root,x);
        if(1<=pos && pos<=n)
        {
            return pos;
        }
        else
        {
            return -1;
        }
    }
    
    /* TODO
     * Function:  num_geq
     * Description:  returns the number of elements in tree which are
     *       greater than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     */
    int num_geq(const T& x) {
        return _num_geq(root,x);  // placeholder
    }

    /*
     * function:     num_geq_SLOW
     * description:  same functionality as num_geq but sloooow (linear time)
     *                (private helper does most of the work)
     *
     */
    int num_geq_SLOW(const T& x) {
        return _num_geq_SLOW(root, x);
    }

private:
    static int _num_geq_SLOW(bst_node* t, const T& x) {
        int total;
        if (t == nullptr) return 0;

       
        total = _num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

        if (t->val >= x)
            total++;
        return total;
    }

    //recursive helper function MY WORK
    static int _num_geq(bst_node* t, const T& x)
    {
        
         if(t==nullptr)
         {
             return 0;
         }
    
         if(t->val >= x)
         {
             return  _num_geq(t->left,x)+t->Rsize+1;
         }
         else
         {
             return  _num_geq(t->right, x);
         }
    }

    //recursive helper function MY WORK
    int _position_of(bst_node* t,  const T& x)
    {
        if(t== nullptr)
        {
            return 0;
        }

        if(x == t->val)
        {
            return 1 + t->Lsize;
        }
        else if(x < t->val)
        {
            return  _position_of(t->left, x);
        }
        else
        {
            return 1 + _position_of(t->right, x) +  t->Lsize;
        }
       
    }

public:

    /* TODO
     * Function:  num_leq
     * Description:  returns the number of elements in tree which are less
     *      than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_leq(const T& x) {
        return _num_leq(root,x); 
    }

    /*
     * function:     num_leq_SLOW
     * description:  same functionality as num_leq but sloooow (linear time)
     *               (private helper _num_leq_SLOW does most of the work)
     */
    int num_leq_SLOW(const T& x) {
        return _num_leq_SLOW(root, x);
    }
private:

    // helper for num_leq_SLOW
    static int _num_leq_SLOW(bst_node* t, const T& x) {
        int total;

        if (t == nullptr) return 0;
        total = _num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

        if (t->val <= x)
            total++;
        return total;
    }

    //recursive helper function MY WORK
    static int _num_leq(bst_node* t, const T& x)
    {
        if (t == nullptr)
        {
            return 0;
        }
        if (t->val <= x)
        {
            return  _num_leq(t->right, x) + t->Lsize + 1;
        }
        else
        {
            return _num_leq(t->left, x);
        }
    }
public:

    /* TODO
     * Function:  num_range
     * Description:  returns the number of elements in tree which are
     *       between min and max (inclusive).
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_range(const T& min, const T& max) {
        return num_leq(max) - _num_range(root,min);
    }

    /*
     * function:     num_range_SLOW
     * description:  same functionality as num_range but sloooow (linear time)
     *               (private helper _num_range_SLOW does most of the work)
     *
     */
    int num_range_SLOW(const T& min, const T& max) {
        return _num_range_SLOW(root, min, max);
    }

private:
    static int _num_range_SLOW(bst_node* t, const T& min, const T& max) {
        int total;

        if (t == nullptr) return 0;
      
        total = _num_range_SLOW(t->left, min, max) +
            _num_range_SLOW(t->right, min, max);

        if (t->val >= min && t->val <= max)
            total++;
        return total;
    }
    
    static int _num_range(bst_node* t, const T& x)
    {
        if (t == nullptr)
        {
            return 0;
        }
        if (t->val < x)
        {
            return  _num_range(t->right, x) + t->Lsize + 1;
        }
        else
        {
            return  _num_range(t->left, x);
        }
    }

   
public:

    /*
     * TODO
     * function:     extract_range
     * Description:  allocates a vector of element type T
     *               and populates it with the tree elements
     *               between min and max (inclusive) in order.
     *               A pointer to the allocated and populated
     *               is returned.
     *
     * notes/comments:  even if the specified range is empty, a
     *                  vector is still allocated and returned;
     *                  that vector just happens to be empty.
     *                  (The function NEVER returns nullptr).
     *
     * runtime:  the runtime requirement is "output dependent".
     *           Let k be the number of elements in the specified range
     *           (and so the length of the resulting vector) and let h
     *           be the height of the tree.  The runtime must be:
     *
     *                  O(h + k)
     *
     *           So...while k can be as large as n, it can be as small
     *           as zero.
     *
     */
    std::vector<T>* extract_range(const T& min, const T& max) 
    {
        vector<T>* vec = new vector<T>();
        _extract_range(root,vec, min, max);
        return vec;
        
    }

    /***************************************************
    *  PREORDER AND INORDER TREE TRAVERSALS BELOW      *
    *                                                  *
    ***************************************************/
    
private:
    static void  _extract_range(bst_node* t, vector<T>* vec,const T& min, const T& max)
    {
        if(t==nullptr)
        {
            return;
        }

        if(t->val >=min&& t->val <= max)
        {
            
            _extract_range(t->left, vec, min, max);
            vec->push_back(t->val);
            _extract_range(t->right, vec, min, max);
            return;
        }
        else if(t->val < min)
        {
            _extract_range(t->right, vec, min, max);
            return;
        }
        else
        {
            _extract_range(t->left, vec, min, max);
            return;
        }
    }

    

    static void indent(int m) {
        int i;
        for (i = 0; i < m; i++)
            std::cout << "-";
    }

    static void _inorder(bst_node* r) {
        if (r == nullptr) return;
        _inorder(r->left);
        std::cout << "[ " << r->val << " ]\n";
        _inorder(r->right);
    }

    static void _preorder(bst_node* r, int margin) {
        if (r == nullptr) {
            indent(margin);
            std::cout << " nullptr \n";
        }
        else {
            indent(margin);
            std::cout << "[ " << r->val << " ]\n";
            _preorder(r->left, margin + 3);
            _preorder(r->right, margin + 3);
        }
    }

public:
    void inorder() {
        std::cout << "\n======== BEGIN INORDER ============\n";
        _inorder(root);
        std::cout << "\n========  END INORDER  ============\n";
    }


    void preorder() {

        std::cout << "\n======== BEGIN PREORDER ============\n";
        _preorder(root, 0);
        std::cout << "\n========  END PREORDER  ============\n";

    }

    /***************************************************
    *  END PREORDER AND INORDER TREE TRAVERSALS        *
    *                                                  *
    ***************************************************/

private:
    /*
     * Recursive  helper function _from_vec, used by
     * from_sorted_arr(...). The function must return a sub-tree that is
     * perfectly balanced, given a sorted array of elements a.
     */
    static bst_node* _from_vec(const std::vector<T>& a, int low, int hi) {
        int m;
        bst_node* root;

        if (hi < low) { 
            return nullptr;
        }
        m = (low + hi) / 2;
        root = new bst_node(a[m]);
        root->left = _from_vec(a, low, m - 1);
        root->right = _from_vec(a, m + 1, hi);

        if (root->left!=nullptr) {
            root->Lsize = root->left->treeSize;
        }
        if (root->right != nullptr) {
            root->Rsize = root->right->treeSize;
        }
       
        root->treeSize = root->Lsize + root->Rsize + 1;
        return root;

    }

public:
    static bst* from_sorted_vec(const std::vector<T>& a, int n) {

        bst* t = new bst();
        t->root = _from_vec(a, 0, n - 1);
        return t;
    }

    static bst_node* SizeBal(bst_node* t)
    {
        vector<bst_node*> vec;
         Bal_vec(vec, t);
        return Bal_Tree(vec, 0, vec.size()-1);
    }
private:
    static bst_node* Bal_Tree(vector<bst_node*>& t, int low, int hi)
    {
        int m;
        bst_node* r;
       
        if (hi < low) 
        {
            return nullptr;
        }
        m = (low + hi) / 2;
        r = t[m];
        r->left = Bal_Tree(t, low, m - 1);
        r->right = Bal_Tree(t, m + 1, hi);
       
        if (r->left != nullptr) {
            r->Lsize = r->left->treeSize;
            r->left->prev = r;
           
        }
        if (r->right != nullptr) {
            r->Rsize = r->right->treeSize;
            r->right->prev = r;
           
        }
       
        r->treeSize = r->Lsize + r->Rsize + 1;
        return r;
    }

    static void Bal_vec(vector<bst_node*>& t, bst_node* r)
    {
        if (r == nullptr)
        {
            return;
        }
        Bal_vec( t,r->left);
        r->Lsize = 0;
        r->Rsize = 0;
        r->treeSize = r->Lsize+ r->Rsize + 1;
        r->prev =nullptr;
        t.push_back(r);
        Bal_vec(t,r->right);
    }

    /*
     * DO NOT MODIFY THE TWO FUNCTIONS BELOW!!!
     */
    static void _to_preorder_vec(bst_node* t, std::vector<T>& vec) {
        if (t == nullptr) return;
        vec.push_back(t->val);
        _to_preorder_vec(t->left, vec);
        _to_preorder_vec(t->right, vec);
    }
    std::vector<T>* to_preorder_vec() {
        std::vector<T>* vec = new std::vector<T>();
        _to_preorder_vec(root, *vec);
        return vec;
    }

    /*
     * Finally, the data members of the bst class
     */
private:
    bst_node* root;


}; // end class bst

#endif