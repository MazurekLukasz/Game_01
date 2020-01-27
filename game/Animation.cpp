#include "Animation.h"



Animation::Animation(GameDataRef data, sf::Vector2u imageCount, std::string texName):
	_data(data)
{
	this->_imageCount = imageCount;
	this->_switchTime = 0.15f;
	canChange = true;
	_currentImage.x = 0;
	_uvRect.width = _data->assets.GetTexture(texName).getSize().x / float(imageCount.x);
	_uvRect.height = _data->assets.GetTexture(texName).getSize().y / float(imageCount.y);
}


Animation::~Animation()
{
}

void Animation::Update(int row,unsigned int start , unsigned int end , bool faceRight)
{
	_currentImage.y = row;


	if (_clock.getElapsedTime().asSeconds() >= _switchTime)
	{
		_currentImage.x += 1;
		if ((_currentImage.x + start) > end )
		{
			_currentImage.x = 0;
			canChange = true;
		}

		_clock.restart();
	
	}
	


	_uvRect.top = _currentImage.y * _uvRect.height;
	
	if (faceRight)
	{
		_uvRect.left = (_currentImage.x + start) * _uvRect.width;
		_uvRect.width = abs(_uvRect.width);
	}
	else
	{
		_uvRect.left = (_currentImage.x + start +1) * abs(_uvRect.width);
		_uvRect.width = -abs(_uvRect.width);
	}
}