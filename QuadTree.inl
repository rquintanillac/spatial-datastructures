#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
QuadTree<Node, Rectangle, Point>::QuadTree(){
    this->root=nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::insert(Point new_point){
    std::shared_ptr<Node>& target = search(new_point, this->root);
    if(target==nullptr){
        target=std::make_shared<Node>(new_point);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node>& QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node){
    if(node == nullptr){
        return node; //not found
    } else if(node->get_point() == target){
        return node;
    }
    
    auto cur_point = node->get_point();

    const int x=0, y=1;

    if(target.get(x) < cur_point.get(x)){
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NW());
        else
            return search(target, node->SW());
    }else{
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NE());
        else
            return search(target, node->SE());
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target){
    return search(target, this->root);
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region){
    //TODO

    std::vector<Point> result;

    this->range(region,this->root, result);



    return result;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::range (Rectangle region, std::shared_ptr<Node>& root, std::vector<Point> &result) {
    const int x=0, y=1;
    if (root == nullptr) {
        return;
    }

    auto cur_point = root->get_point();

    if(cur_point.get(x) >= region._min.get(x) && cur_point.get(x) <= region._max.get(x) && cur_point.get(y) >= region._min.get(y) && cur_point.get(y)<=region._max.get(y)){
        result.push_back(cur_point);
    }

    if (region._min.get(x) <= cur_point.get(x) && region._min.get(y) <= cur_point.get(y)) {
        range(region, root->SW(),result);
        
    }
    if (region._min.get(x) <= cur_point.get(x) && region._max.get(y) >= cur_point.get(y)) {
        range(region, root->NW(),result);
        
    }
    if (region._max.get(x) >= cur_point.get(x) && region._min.get(y) <= cur_point.get(y)) {
        range(region, root->SE(),result);
        
    }
    if (region._max.get(x) >= cur_point.get(x) && region._max.get(y) >= cur_point.get(y)) {
        range(region, root->NE(),result);
        
    }
}



template<typename Node, typename Rectangle, typename Point>
Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference){
    // TODO
}

} //spatial
} //utec
