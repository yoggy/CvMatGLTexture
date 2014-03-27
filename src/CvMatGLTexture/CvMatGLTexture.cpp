#include "StdAfx.h"
#include "CvMatGLTexture.h"


CvMatGLTexture::CvMatGLTexture() 
	: is_init_(false), texture_id_(0), texture_size_(512, 512)
{

}

CvMatGLTexture::CvMatGLTexture(const int &texture_width, const int &texture_height) 
	: is_init_(false), texture_id_(0), texture_size_(texture_width, texture_height)
{

}

CvMatGLTexture::CvMatGLTexture(const cv::Size &texture_size) 
	: is_init_(false), texture_id_(0), texture_size_(texture_size)
{

}

CvMatGLTexture::~CvMatGLTexture()
{
	finish();
}

bool CvMatGLTexture::is_init() const
{
	return this->is_init_;
}

cv::Size CvMatGLTexture::texture_size() const
{
	return this->texture_size_;
}

void CvMatGLTexture::texture_size(const cv::Size &val)
{
	this->texture_size_ = val;
}

void CvMatGLTexture::texture_size(const int &width, const int &height)
{
	this->texture_size_ = cv::Size(width, height);
}

bool CvMatGLTexture::init()
{
	if (is_init()) return false;

	glGenTextures(1, &texture_id_);
	if (texture_id_ == 0) return false;

	glBindTexture(GL_TEXTURE_2D, texture_id_);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D,        // target
		0,                    // mipmap level
		GL_RGB,               // internal format
		texture_size_.width,  // width
		texture_size_.height, // height
		0,                    // border
		GL_BGR_EXT,           // format
		GL_UNSIGNED_BYTE,     // type
		NULL                  // data
		);

	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	is_init_ = true;
}

void CvMatGLTexture::finish()
{
	if (is_init() == true) {
		glDeleteTextures(1, &texture_id_);
		texture_id_ = 0;
	}
	is_init_ = false;
}

bool CvMatGLTexture::image(const cv::Mat &texture_img)
{
	if (texture_img.empty()) return false;
	if (is_init() == false) init();

	cv::Mat target;
	if (texture_img.size() == texture_size_) {
		target = texture_img;
	}
	else {
		cv::resize(texture_img, target, texture_size_);
	}

	glBindTexture(GL_TEXTURE_2D, texture_id_);

	// replace texture image
	glTexSubImage2D(
		GL_TEXTURE_2D,        // target
		0,                    // mipmap level
		0,                    // x offset
		0,                    // y offset
		texture_size_.width,  // width
		texture_size_.height, // height
		GL_BGR_EXT,           // format
		GL_UNSIGNED_BYTE,     // type
		target.data      // data
		);

	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void CvMatGLTexture::bind_texture()
{
	glBindTexture(GL_TEXTURE_2D, texture_id_);
}
