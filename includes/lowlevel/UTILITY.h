#include <filesystem>
#include <shellapi.h>
#include <algorithm>
#include <thread>

//prototypes
inline double is_in_slider(double value);
inline void ex_textfile(std::string path);
inline std::vector<std::string> listdir(std::string path);
inline float distance(float x1, float y1, float x2, float y2);
inline float calc_area(float a, float b, float c);
inline int position(float area, float A, float B, float C);
inline void calc(float x1, float y1, float x2, float y2
	, float x3, float y3, float x, float y, int* flag, float* area);
inline bool isInTriangle(glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 point);
inline glm::vec4 return_ndc_cursor(GLFWwindow* window);
inline void download(std::string text);
inline void InitDownload(std::string text);




inline double is_in_slider(double value) {
	if (value < -0.5) {
		value = -0.5;
	}
	if (value > 0.462) {
		value = 0.462;
	}
	return value;
}
inline void ex_textfile(std::string path) {
	ShellExecuteA(GetDesktopWindow(), "open", path.c_str(), NULL, NULL, SW_SHOW);
}
inline std::vector<std::string> listdir(std::string path) {
	std::vector<std::string> items;
	for (auto& p : std::filesystem::directory_iterator(path)) {
		std::string item = p.path().string();
		items.push_back(item.erase(0, path.size() + 1));
	}
	return items;
}
/*
<distance> <calc_area> <position> < calc > <IsInTriangle>
 -- are used for input proccesing

 -- use IsInTriangle to check for where is a point

*/
// calculate distance beetween (x1,y1) ----- (x2,y2)
inline float distance(float x1, float y1, float x2, float y2)
{
	return(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}
// calculates the surface of a triangle with points a b c
inline float calc_area(float a, float b, float c)
{
	float S;

	S = (a + b + c) / 2.0;

	return(sqrt(S * (S - a) * (S - b) * (S - c)));
}
// modulus
inline int position(float area, float A, float B, float C)
{
	float res = area - (A + B + C);

	if (res < 0)
	{
		res *= -1;
	}

	if (res == 0 || res < 0.001)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}
//calculates if a point (x,y) is in the triangle A(x1,y1) B(x2,y2) , C(x3,y3)
inline void calc(float x1, float y1, float x2, float y2
	, float x3, float y3, float x, float y, int* flag, float* area) {
	/*
	* https://www.youtube.com/watch?v=ntjM9YZP0qk
	*
	* the link for the whole IsInTriangle() function explanation

	*/
	float A, B, C, a, b, c, d, e, f;

	a = distance(x1, y1, x2, y2);
	b = distance(x2, y2, x3, y3);
	c = distance(x3, y3, x1, y1);
	*area = calc_area(a, b, c);

	d = distance(x1, y1, x, y);
	e = distance(x2, y2, x, y);
	f = distance(x3, y3, x, y);

	A = calc_area(d, a, e);
	B = calc_area(e, b, f);
	C = calc_area(f, c, d);

	*flag = position(*area, A, B, C);
}
// C++ implementation of C function calc()
inline bool isInTriangle(glm::vec4 A, glm::vec4 B, glm::vec4 C, glm::vec4 point) {
	int   flag = 0;
	float area = 0;

	calc(A.x, A.y, B.x, B.y, C.x, C.y, point.x, point.y, &flag, &area);

	if (flag) return true;
	else  return false;
}
inline glm::vec4 return_ndc_cursor(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	//window pos
	int winx, winy;
	glfwGetWindowPos(window, &winx, &winy);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	ypos = static_cast<double>(height) - ypos;// here we inverse the y axis  from down positive to up positive axis...
	float ndc_x = xpos / width * 2 - 1;// normalizing coordinates x , y
	float ndc_y = ypos / height * 2 - 1;

	glm::vec4 point = glm::vec4(ndc_x, ndc_y, 1.0f, 1.0f);// creating point on screen with normalized coords
	return point;
}
inline void download(std::string text) {
	system((std::string("c: & cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\dependencies & youtube-dl -o ") +
		std::string("C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data\\out.mp4  ") + text).c_str());

	std::vector v = listdir("data");
	if (std::find(v.begin(), v.end(), "out.mp4") != v.end()) {
		/* v contains mp4 file */
		system(std::string("cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data & ffmpeg -i out.mp4 -vn out.mp3 & del out.mp4").c_str());
	}
	if (std::find(v.begin(), v.end(), "out.mkv") != v.end()) {
		/* v contains mkv file */
		system(std::string("cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data & ffmpeg -i out.mkv -vn out.mp3 & del out.mkv").c_str());
	}
	else {
		/* v does not contain any supported format */
		printf("\n Failed to download video ");
		printf(text.c_str());
		printf("\n");
	}
}
inline void InitDownload(std::string text) {
	std::thread downloader = std::thread(&download, text);
	downloader.detach();
}