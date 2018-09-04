/*
** EPITECH PROJECT, 2018
** BombStandard
** File description:
** Class bomb one
*/

#ifndef BOMBSTANDAD_HPP_
	#define BOMBSTANDAD_HPP_

#include "Item.hpp"

class BombStandard : public IItem {
public:
	BombStandard(
		irr::scene::ISceneManager *smgr,
		irr::video::IVideoDriver *driver,
		int range);
	~BombStandard();
	irr::scene::IAnimatedMeshSceneNode* isUsed(float x, float z);
	std::string getItemName();
	int getId();
	bool explodeBomb(int x, int y,
	std::shared_ptr<Map> Map,
	std::vector<std::pair<int, int>> playerPos);
	std::pair<int, int> getPlayerDead() const;
	int	getSpeedBonus() const;
	int	getRangeBonus()  const;
	int	getNbrBombBonus() const;
	void	addBonus(Cube::TypeBox type);
private:
	irr::scene::ISceneManager *_scene;
	irr::video::IVideoDriver *_driver;
	std::string _itemName;
	int _ID;
	irr::scene::IAnimatedMesh* _bombSMesh;
	irr::scene::IAnimatedMeshSceneNode* _bombSNode;
	int _range;
	std::pair<int, int> _playerDead;
	int _speedBonus;
	int _rangeBonus;
	int _nbrBombBonus;
};

#endif /* !BOMBSTANDAD_HPP_ */
