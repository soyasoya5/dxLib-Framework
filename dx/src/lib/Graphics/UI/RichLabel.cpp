#include "RichLabel.h"
#include "../Font.h"
#include "../Text.h"
#include "../Pen.h"
#include "../Texture.h"

begin_UI

RichLabel::RichLabel()
	: Component()
{
	OnModified() += __LIB EventHandler<void(Component*)>("Constructor_Watcher",
		[this](Component *component) { this->_changed = true; });
	_changed = true;
}

void RichLabel::Paint(__GRAPHICS Window * _Sender, __GRAPHICS BasePainter * _Painter)
{
	if (!isVisible())
		return;
	OnPrePaint().Invoke(this, _Painter);

	// Just incase :P
	FlexibleGuard guard{ _kpr };

	auto pos = determineRegion();


	__MATH Vector2 fullsize{ 0, 0 };
	for (auto it = _all_text.begin(), begin = _all_text.begin(), end = _all_text.end(); it < end; ++it)
	{
		// First lets check if we changed
		if (_changed) // If so recalculate everything
		{
			// Check font
			if (!it->container.font)
				it->container.font = (getFont() ? getFont() : _Painter->defaultFont());

			// Recalculate position
			if (it == begin) // First...
			{
				it->position = pos.position;
				it->container.orig_tex_y = it->position.y;
			}
			else
			{
				auto prev = (it - 1);

				// did the previus node end on a new line
				if (prev->container.new_line) {
					it->position = { pos.position.x, prev->position.y + prev->size.y }; // kk then get original x pos and the prev y + its size
					it->container.orig_tex_y = it->position.y;
				}
				else if (it->container.is_texture)
				{
					it->position.x = prev->position.x + prev->size.x + 8;
					it->position.y = (prev->size.y / 2 - it->container.texture->getSize().y / 2) + prev->position.y;
					it->container.orig_tex_y = prev->container.orig_tex_y;
				}
				else
				{
					// Is prev texture
					if (prev->container.is_texture)
					{
						// Set x
						it->position.x = prev->position.x + prev->size.x;

						// Now allign y PROPERLY.
						it->position.y = prev->container.orig_tex_y;

						// Set this ones orig_tex_y
						it->container.orig_tex_y = prev->container.orig_tex_y;
					}
					else
					{
						// Set position
						it->position = prev->position + __MATH Vector2{ prev->size.x, 0.0f }; // Ok then get the vector of prev pos + prev size(x only)

																							  // Set orig
						it->container.orig_tex_y = it->position.y;
					}
				}
			}

			// Size
			it->size = (it->container.is_texture ? it->container.texture->getSize() : it->container.font->calculateMetrixOf(it->container.text));
			if (it->container.new_line)
				fullsize.y += it->size.y;
			else if (it->size.x > fullsize.x)
				fullsize.x = it->size.x;
		}
		// Right, lets draw
		if (it->container.is_texture)
			it->container.texture->Paint(it->position, { 1, 1 });
		else
		{
			Text text;
			text.setPosition(it->position);
			text.setFont(it->container.font);
			text.setText(it->container.text);
			text.setMaxClip(it->size);

			// Paintaronie
			_Painter->Paint(text, Pen(it->container.color, 1));
		}
	}

	// We dont wanna raise a modified event if its not needed, obviously.
	if (getSize() != fullsize)
		this->setSize(fullsize);

	_changed = false;
	OnPostPaint().Invoke(this, _Painter);
}

void RichLabel::appendText(const __LIB String & _Text, __GRAPHICS Font * _Font, const __DX uint & _Color)
{
	_mtext.append(_Text);

	if (_Text.contains("\n"))
	{
		auto vecs = _Text.split('\n');
		for (auto text : vecs)
		{
			TextContainer container;
			container.text = text;
			container.font = _Font;
			container.color = _Color;
			container.new_line = true;
			container.is_texture = false;
			container.is_selected = false;
			_contrs.push_back(std::move(container));
		}
	}
	else
	{
		TextContainer container;
		container.text = _Text;
		container.font = _Font;
		container.color = _Color;
		container.new_line = false;
		container.is_texture = false;
		container.is_selected = false;
		_contrs.push_back(std::move(container));
	}

	OnModified().Invoke(this);
	recalculate_text();
}

void RichLabel::appendText(const __LIB String & _Text, __GRAPHICS Font * _Font)
{
	appendText(_Text, _Font, __DX Colors::White);
}

void RichLabel::appendText(const __LIB String & _Text, const __DX uint & _Color)
{
	appendText(_Text, getFont(), _Color);
}

void RichLabel::appendText(const __LIB String & _Text)
{
	appendText(_Text, getFont(), __DX Colors::White);
}

void RichLabel::appendText(__GRAPHICS Texture * _Texture)
{
	if (_Texture->getSize() > __MATH Vector2{ 64, 64 })
		return;
	TextContainer container;
	container.text = "";
	container.font = nullptr;
	container.color = 0;
	container.new_line = false;
	container.is_selected = false;
	container.is_texture = true;
	container.texture = _Texture;
	_contrs.push_back(std::move(container));
	OnModified().Invoke(this);
	recalculate_text();
}

__LIB String RichLabel::getText() const
{
	return _mtext;
}

void RichLabel::setText(const __LIB String & _Text)
{
	_contrs.clear();
	_contrs.push_back(TextContainer{ nullptr, _Text, __DX Colors::White, getFont(), false, false });
	recalculate_text();
}

RichLabel::RichText * RichLabel::textAt(const int & index)
{
	return &_all_text[index];
}

RichLabel::RichText * RichLabel::textFrom(const std::function<bool(RichText*text)>& _Functor)
{
	for (auto it = _all_text.begin(); it < _all_text.end(); ++it)
		if (_Functor(&(*it)))
			return &(*it);
	return nullptr;
}

RichLabel::RichText * RichLabel::textFromText(const __LIB String & _Text)
{
	for (auto it = _all_text.begin(); it < _all_text.end(); ++it)
		if (it->container.text == _Text)
			return &(*it);
	return nullptr;
}

RichLabel::RichText * RichLabel::textInRegion(const __MATH Region & _Region)
{
	for (auto it = _all_text.begin(); it < _all_text.end(); ++it)
	{
		if (it->position.Intersects(_Region))
			return &(*it);
	}
	return nullptr;
}

void RichLabel::clearText()
{
	_text = "";
	_all_text.clear();
	_contrs.clear();
	_mtext = "";
	_changed = true;
}

AsyncKeeper & RichLabel::AquireMutex()
{
	return _kpr;
}

void RichLabel::recalculate_text()
{
	// Setup ze mutex just incase some retard appends text in another thread :|
	AsyncGuard guard{ _kpr };

	// Clear text container
	_all_text.clear();

	for (auto cont : _contrs)
	{
		RichText text;
		text.container = cont;
		text.position = { -1, -1 };
		text.size = { -1, -1 };
		_all_text.push_back(text);
	}

}




end_UI