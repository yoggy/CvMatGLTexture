#pragma once

#pragma warning(disable:4098)
#include <GL/GL.h>
#include <opencv2/core/core.hpp>

class CvMatGLTexture
{
public:
	CvMatGLTexture();
	CvMatGLTexture(const int &texture_width, const int &texture_height);
	CvMatGLTexture(const cv::Size &texture_size);

	virtual ~CvMatGLTexture(void);

	bool is_init() const;

	cv::Size texture_size() const;
	void texture_size(const cv::Size &val);
	void texture_size(const int &width, const int &height);

	bool init();
	void finish();

	bool image(const cv::Mat &texture_img);
	void bind_texture();

protected:
	bool is_init_;
	cv::Size texture_size_;
	GLuint texture_id_;
};

