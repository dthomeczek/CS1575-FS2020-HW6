/* Define all your MyMap-related functions here, including the get_identity
    function
 * You do not need to include MyMap.h in this hpp header file. It includes
    this file at the bottom.
 */

// The usual identity function again
void get_identity(std::string &my_id)
{
   my_id = "djtpfr";
}

template<typename K, typename V>
V & MyMap<K, V>::at_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
   MyPair<K, V> *tmp = find_helper(rt, key);

   if (tmp == nullptr)
   {
      throw std::out_of_range("MyMap::at\n");
   }
   else if (rt -> data.first == key)
   {
      return rt -> data.second;
   }
   else
   {
      return tmp -> second;
   }
}

template<typename K, typename V>
int MyMap<K, V>::size_helper(TreeNode<MyPair<K,V>> *rt) const
{
   if (rt == nullptr)
   {
      return 0;
   }
   return int (1 + size_helper(rt -> left) + size_helper(rt -> right));
}

template<typename K, typename V>
void MyMap<K, V>::clear_helper(TreeNode<MyPair<K, V>> *&rt)
{
   if (rt == nullptr)
   {
      return;
   }
   clear_helper(rt -> left);
   clear_helper(rt -> right);
   delete rt;
   rt = nullptr;
}

template<typename K, typename V>
void MyMap<K, V>::insert_helper(TreeNode<MyPair<K, V>> *&rt, const MyPair<K, V> &init_pair)
{
   if (rt == nullptr)
   {
      rt = new TreeNode<MyPair<K, V>>(init_pair, nullptr, nullptr);
   }
   else if (init_pair.first < rt -> data.first)
   {
      insert_helper(rt -> left, init_pair);
   }
   else
   {
      insert_helper(rt -> right, init_pair);
   }
}

template<typename K, typename V>
TreeNode<MyPair<K, V>> * MyMap<K, V>::get_min(TreeNode<MyPair<K, V>> *rt)
{
   if(rt -> left == nullptr)
   {
      return rt;
   }
   else
   {
      return get_min(rt -> left);
   }
}

template<typename K, typename V>
void MyMap<K, V>::erase_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
   if (rt == nullptr)
   {
      return;
   }
   else if (key < rt -> data.first)
   {
      erase_helper(rt -> left, key);
   }
   else if (key > rt -> data.first)
   {
      erase_helper(rt -> right, key);
   }
   else
   {
      if (rt -> left == nullptr)
      {
         rt = rt -> right;
      }
      else if (rt -> right == nullptr)   
      {
         rt = rt -> left;
      }
      else
      {        
         TreeNode<MyPair<K, V>> *minimum = get_min(rt -> right);
         TreeNode<MyPair<K, V>> *point = rt -> right;
         if (minimum == point)
         {
            rt -> data = minimum -> data;
            rt -> right = minimum -> right;
         }      
         else
         {
            if (point -> left != nullptr)
            {
               TreeNode<MyPair<K, V>> *rtleft = point -> left;
               TreeNode<MyPair<K, V>> *rtleftpd = rt -> right;
               while (rtleft -> left != nullptr)
               {
                  rtleftpd = rtleft;
                  rtleft = rtleft -> left;
               }
               rt -> data = rtleft -> data;
               rtleftpd -> left = rtleft -> right;
               delete rtleft;
            }   
            else
            {
               TreeNode<MyPair<K, V>> *tmp = rt -> right;
               rt -> data = tmp -> data;
               rt -> right = tmp -> right;
               delete tmp;
            }
         }
      }  
   }
}

template<typename K, typename V>
MyPair<K, V> * MyMap<K, V>::find_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
   if (rt == nullptr)
   {
      return nullptr;
   }
   if (key < rt -> data.first)
   {
      return find_helper(rt -> left, key);
   }
   else if (key > rt -> data.first)
   {
      return find_helper(rt -> right, key);
   }
   else
   {
      return &(rt -> data);
   }
}

template <typename K, typename V>
void MyMap<K, V>::print_helper(TreeNode<MyPair<K, V>> *rt, std::string indent) const
{
   if (rt == nullptr)
   {
      cout << indent << "   [empty]" << endl;
   }
   else
   {
      print_helper(rt -> right, indent += "  ");
      cout << indent << " [" << rt -> data.first << "]=" << rt -> data.second << endl;
      print_helper(rt -> left, indent += "");
   }  
}

template <typename K, typename V>
int MyMap<K, V>::count_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
   int val;
   if (rt == nullptr)
   {
      return 0;
   }
   else if (key == rt -> data.first)
   {
      val = (1 + count_helper(rt -> left, key) + count_helper(rt -> right, key));
   }
   else if (key < rt -> data.first)
   {
      val = count_helper(rt -> left, key);  
   }
   else if (key > rt -> data.first)
   {
      val = count_helper(rt -> right, key);
   }
   return val;
}

template <typename K, typename V>
TreeNode<MyPair<K, V>> * MyMap<K, V>::clone(const TreeNode<MyPair<K, V>> *rt)
{
   V var;
   if (rt == nullptr)
   {
      return nullptr;
   }
   TreeNode<MyPair<K, V>> *tmp = new TreeNode<MyPair<K, V>>(MyPair<K, V>(0, var), nullptr, nullptr);

   tmp -> data.first = rt -> data.first;
   tmp -> data.second = rt -> data.second;
   tmp -> left = clone(rt -> left);   
   tmp -> right = clone(rt -> right);
   return tmp;
}

template <typename K, typename V>
MyMap<K, V>::MyMap()
{
   root = nullptr;
}

template <typename K, typename V>
MyMap<K, V>::~MyMap()
{
   clear_helper(root);
}

template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap<K, V> &source)
{
   root = clone(source.root);
}

template <typename K, typename V>
MyMap<K, V> & MyMap<K, V>::operator=(const MyMap<K, V> &source)
{
   if (this != &source)
   {
   this -> clear();
   if (source.root == nullptr)
      root = nullptr;
   else
      root = clone(source.root);
   }
   return *this;
}

template <typename K, typename V>
V & MyMap<K, V>::at(const K &key)
{
   return at_helper(root, key);
}

template <typename K, typename V>
V & MyMap<K, V>::operator[](const K &key)
{
   if (find(key) == nullptr)
   {
      V var;
      insert(MyPair<K, V>(key, var));
      return at(key);
   }

   return at(key);
}

template <typename K, typename V>
bool MyMap<K, V>::empty() const
{
   return (root == nullptr);
}

template <typename K, typename V>
int MyMap<K, V>::size() const
{
   return size_helper(root);
}

template <typename K, typename V>
void MyMap<K, V>::clear()
{
   clear_helper(root);
   root = nullptr;
}

template <typename K, typename V>
void MyMap<K, V>::insert(const MyPair<K, V> &init_pair)
{
   insert_helper(root, init_pair);
}

template <typename K, typename V>
void MyMap<K, V>::erase(const K &key)
{
   erase_helper(root, key);
}

template <typename K, typename V>
MyPair<K, V> * MyMap<K, V>::find(const K &key) const
{
   return find_helper(root, key);
}

template <typename K, typename V>
void MyMap<K, V>::print() const
{
   if (root == nullptr)
      cout << "   [empty]" << endl;
   else
      print_helper(root, "");
}

template <typename K, typename V>
int MyMap<K, V>::count(const K &key) const
{
   return count_helper(root, key);
}

void get_letter_frequency(MyMap<char, int> &in_tree)
{
   in_tree.clear();
   char input;

   while (cin.get(input))
   {
      if (input !='\n')
      {
         if (in_tree.find(input) == nullptr)
         {
            in_tree[input] = 1;
         }
         else
         {
            in_tree[input] += 1;
         }
      }
   }
   in_tree.print();
}