#include "grenderenginedata.h"
#include "gimagedata.h"
#include "gsfmlutil.h"

namespace gincu {

GRenderEngineData::GRenderEngineData()
	:
		window(),
		view(),
		batchDrawVertexArray(sf::Triangles),
		batchDrawRenderInfo(),
		inBatchDraw(false)
{
}

void GRenderEngineData::clearBatchDrawState() {
	this->batchDrawVertexArray.clear();
	this->batchDrawImageData.reset();
	this->inBatchDraw = false;
}

void GRenderEngineData::directDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	const sf::Transform & sfmlTransform = transform.getSfmlTransform();

	sf::Sprite sprite(texture->texture, { (int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height });
	sf::RenderStates renderStates(sfmlTransform);
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->window->draw(sprite, renderStates);
}

void GRenderEngineData::batchDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	const sf::Transform & sfmlTransform = transform.getSfmlTransform();

	this->batchDrawRenderInfo = *renderInfo;
	this->batchDrawImageData = texture;

	sf::VertexArray & vertexArray = this->batchDrawVertexArray;
	std::size_t count = vertexArray.getVertexCount();
	vertexArray.resize(count + 6);

	vertexArray[count].position = sfmlTransform.transformPoint({ 0, 0 });
	vertexArray[count].texCoords = { rect.x, rect.y };
	++count;
	vertexArray[count].position = sfmlTransform.transformPoint({ rect.width, 0 });
	vertexArray[count].texCoords = { rect.x + rect.width, rect.y };
	++count;
	vertexArray[count].position = sfmlTransform.transformPoint({ rect.width, rect.height });
	vertexArray[count].texCoords = { rect.x + rect.width, rect.y + rect.height };
	++count;

	vertexArray[count].position = sfmlTransform.transformPoint({ rect.width, rect.height });
	vertexArray[count].texCoords = { rect.x + rect.width, rect.y + rect.height };
	++count;
	vertexArray[count].position = sfmlTransform.transformPoint({ 0, rect.height });
	vertexArray[count].texCoords = { rect.x, rect.y + rect.height };
	++count;
	vertexArray[count].position = sfmlTransform.transformPoint({ 0, 0 });
	vertexArray[count].texCoords = { rect.x, rect.y };
}


} //namespace gincu

