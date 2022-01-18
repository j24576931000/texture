#pragma once

//#include "GL/glew.h"
//#include "GLFW/glfw3.h"
//#include "ResourcePath.h"
#include "MeshObject.h"
#include "DrawModelShader.h"
#include "DrawCutShader.h"
#include "PickingShader.h"
#include "PickingTexture.h"
#include "DrawPickingFaceShader.h"
#include "ViewManager.h"
#include "DotNetUtilities.h"
#include "DrawPointShader.h"
//#include "Mesh/GUA_OM.h"
//#include "Mesh/DP.h"
//#include "Mesh/XForm.h"
//#include "Mesh/GLCamera.h"
#include <vector>

//const std::string ProjectName = "OpenMesh_EX";
glm::vec3 worldPos;
bool updateFlag = false;

GLuint faceID = 0;
//bool isRightButtonPress = false;
GLuint currentFaceID = 0;
int currentMouseX = 0;
int currentMouseY = 0;
int windowWidth = 800;
int windowHeight = 600;
int selectionMode = 1;
GLuint			program;			// shader program
glm::mat4		proj_matrix;		// projection matrix
float			aspect;
ViewManager		meshWindowCam;
GLuint texture;
MeshObject model;

// shaders
DrawModelShader drawModelShader;
DrawCutShader drawCutShader;
DrawPickingFaceShader drawPickingFaceShader;
PickingShader pickingShader;
PickingTexture pickingTexture;
DrawPointShader drawPointShader;
bool light = true;
// vbo for drawing point
GLuint vboPoint;
float rotation = 0.0f, scal = 0.0f, translat = 0.0f;
bool render_tex = false;
std::vector<GLuint> id;
int tex_id = 0;
//Tri_Mesh *mesh;
bool edit_mode = false;
int edit_num = 1;
bool isloading = false;
int num2;
//xform xf;
//GLCamera camera;
//float fov = 0.7f;

/*static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};
Mouse::button Mouse_State = Mouse::ROTATE;*/

namespace OpenMesh_EX {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadModelToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::Panel^  panel1;

	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Button^  edit;
	private: System::Windows::Forms::Button^  move_right;

	private: System::Windows::Forms::Button^  move_left;
	private: System::Windows::Forms::Button^  rotate;


	private: System::Windows::Forms::Button^  zoom_out;

	private: System::Windows::Forms::Button^  zoom_in;
	private: System::Windows::Forms::Button^  mesh_zoom_out;
	private: System::Windows::Forms::Button^  mesh_zoom_in;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  reset;
	private: System::Windows::Forms::ToolStripMenuItem^  loadTextureToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openTexFileDialog;
	private: System::Windows::Forms::OpenFileDialog^  pictureBoxDialog;	
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  multiselect;
			 //array<PictureBox^> ^pic = gcnew array<PictureBox^>(10);
	PictureBox^ pic_init;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{		
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadTextureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->reset = (gcnew System::Windows::Forms::Button());
			this->mesh_zoom_in = (gcnew System::Windows::Forms::Button());
			this->mesh_zoom_out = (gcnew System::Windows::Forms::Button());
			this->zoom_in = (gcnew System::Windows::Forms::Button());
			this->move_right = (gcnew System::Windows::Forms::Button());
			this->zoom_out = (gcnew System::Windows::Forms::Button());
			this->move_left = (gcnew System::Windows::Forms::Button());
			this->rotate = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->edit = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->openTexFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBoxDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->multiselect = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->panel2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(800, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->loadModelToolStripMenuItem,
					this->saveModelToolStripMenuItem, this->loadTextureToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveModelToolStripMenuItem_Click);
			// 
			// loadTextureToolStripMenuItem
			// 
			this->loadTextureToolStripMenuItem->Name = L"loadTextureToolStripMenuItem";
			this->loadTextureToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->loadTextureToolStripMenuItem->Text = L"Load Texture";
			this->loadTextureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadTextureToolStripMenuItem_Click);
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveModelDialog_FileOk);
			// 
			// hkoglPanelControl1
			// 
			this->hkoglPanelControl1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"hkoglPanelControl1.BackgroundImage")));
			this->hkoglPanelControl1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 24);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(800, 600);
			this->hkoglPanelControl1->TabIndex = 2;
			this->hkoglPanelControl1->Tag = L"-1";
			this->hkoglPanelControl1->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::hkoglPanelControl1_KeyPress);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseWheel);
			this->hkoglPanelControl1->Resize += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Resize);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->ImageAlign = System::Drawing::ContentAlignment::TopRight;
			this->button1->Location = System::Drawing::Point(725, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"create texture";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->groupBox2);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Controls->Add(this->numericUpDown1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel1->Location = System::Drawing::Point(600, 24);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 600);
			this->panel1->TabIndex = 4;
			// 
			// groupBox2
			// 
			this->groupBox2->AutoSize = true;
			this->groupBox2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->groupBox2->Location = System::Drawing::Point(14, 171);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(6, 5);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"groupBox2";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Location = System::Drawing::Point(53, 104);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 50);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Tag = L"-1";
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(14, 41);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(34, 22);
			this->textBox1->TabIndex = 1;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(68, 42);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 22);
			this->numericUpDown1->TabIndex = 0;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->multiselect);
			this->panel2->Controls->Add(this->groupBox1);
			this->panel2->Controls->Add(this->checkBox1);
			this->panel2->Controls->Add(this->button3);
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->edit);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 24);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(200, 600);
			this->panel2->TabIndex = 5;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->reset);
			this->groupBox1->Controls->Add(this->mesh_zoom_in);
			this->groupBox1->Controls->Add(this->mesh_zoom_out);
			this->groupBox1->Controls->Add(this->zoom_in);
			this->groupBox1->Controls->Add(this->move_right);
			this->groupBox1->Controls->Add(this->zoom_out);
			this->groupBox1->Controls->Add(this->move_left);
			this->groupBox1->Controls->Add(this->rotate);
			this->groupBox1->Location = System::Drawing::Point(12, 171);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(180, 395);
			this->groupBox1->TabIndex = 18;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"groupBox1";
			// 
			// reset
			// 
			this->reset->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->reset->Location = System::Drawing::Point(70, 328);
			this->reset->Name = L"reset";
			this->reset->Size = System::Drawing::Size(50, 50);
			this->reset->TabIndex = 15;
			this->reset->Text = L"reset";
			this->reset->UseVisualStyleBackColor = false;
			this->reset->Click += gcnew System::EventHandler(this, &MyForm::reset_Click);
			// 
			// mesh_zoom_in
			// 
			this->mesh_zoom_in->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"mesh_zoom_in.BackgroundImage")));
			this->mesh_zoom_in->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->mesh_zoom_in->Location = System::Drawing::Point(18, 31);
			this->mesh_zoom_in->Name = L"mesh_zoom_in";
			this->mesh_zoom_in->Size = System::Drawing::Size(50, 50);
			this->mesh_zoom_in->TabIndex = 13;
			this->mesh_zoom_in->UseVisualStyleBackColor = true;
			this->mesh_zoom_in->Click += gcnew System::EventHandler(this, &MyForm::mesh_zoom_in_Click);
			// 
			// mesh_zoom_out
			// 
			this->mesh_zoom_out->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"mesh_zoom_out.BackgroundImage")));
			this->mesh_zoom_out->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->mesh_zoom_out->Location = System::Drawing::Point(122, 31);
			this->mesh_zoom_out->Name = L"mesh_zoom_out";
			this->mesh_zoom_out->Size = System::Drawing::Size(50, 50);
			this->mesh_zoom_out->TabIndex = 14;
			this->mesh_zoom_out->UseVisualStyleBackColor = true;
			this->mesh_zoom_out->Click += gcnew System::EventHandler(this, &MyForm::mesh_zoom_out_Click);
			// 
			// zoom_in
			// 
			this->zoom_in->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"zoom_in.BackgroundImage")));
			this->zoom_in->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->zoom_in->Location = System::Drawing::Point(18, 104);
			this->zoom_in->Name = L"zoom_in";
			this->zoom_in->Size = System::Drawing::Size(50, 50);
			this->zoom_in->TabIndex = 7;
			this->zoom_in->UseVisualStyleBackColor = true;
			this->zoom_in->Click += gcnew System::EventHandler(this, &MyForm::zoom_in_Click);
			// 
			// move_right
			// 
			this->move_right->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"move_right.BackgroundImage")));
			this->move_right->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->move_right->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"move_right.Image")));
			this->move_right->ImageAlign = System::Drawing::ContentAlignment::TopCenter;
			this->move_right->Location = System::Drawing::Point(122, 255);
			this->move_right->Name = L"move_right";
			this->move_right->Size = System::Drawing::Size(50, 50);
			this->move_right->TabIndex = 11;
			this->move_right->UseVisualStyleBackColor = true;
			this->move_right->Click += gcnew System::EventHandler(this, &MyForm::move_right_Click);
			// 
			// zoom_out
			// 
			this->zoom_out->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"zoom_out.BackgroundImage")));
			this->zoom_out->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->zoom_out->Location = System::Drawing::Point(122, 104);
			this->zoom_out->Name = L"zoom_out";
			this->zoom_out->Size = System::Drawing::Size(50, 50);
			this->zoom_out->TabIndex = 8;
			this->zoom_out->UseVisualStyleBackColor = true;
			this->zoom_out->Click += gcnew System::EventHandler(this, &MyForm::zoom_out_Click);
			// 
			// move_left
			// 
			this->move_left->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"move_left.BackgroundImage")));
			this->move_left->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->move_left->Location = System::Drawing::Point(18, 255);
			this->move_left->Name = L"move_left";
			this->move_left->Size = System::Drawing::Size(50, 50);
			this->move_left->TabIndex = 10;
			this->move_left->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->move_left->UseVisualStyleBackColor = true;
			this->move_left->Click += gcnew System::EventHandler(this, &MyForm::move_left_Click);
			// 
			// rotate
			// 
			this->rotate->Location = System::Drawing::Point(70, 182);
			this->rotate->Name = L"rotate";
			this->rotate->Size = System::Drawing::Size(50, 50);
			this->rotate->TabIndex = 9;
			this->rotate->Text = L"↪";
			this->rotate->UseVisualStyleBackColor = true;
			this->rotate->Click += gcnew System::EventHandler(this, &MyForm::rotate_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(69, 572);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(63, 16);
			this->checkBox1->TabIndex = 17;
			this->checkBox1->Text = L"show uv";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button3->Location = System::Drawing::Point(134, 93);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(50, 50);
			this->button3->TabIndex = 16;
			this->button3->Text = L"finished";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button2->Location = System::Drawing::Point(30, 93);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(50, 50);
			this->button2->TabIndex = 15;
			this->button2->Text = L"select_area";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// edit
			// 
			this->edit->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->edit->Location = System::Drawing::Point(30, 25);
			this->edit->Name = L"edit";
			this->edit->Size = System::Drawing::Size(50, 50);
			this->edit->TabIndex = 6;
			this->edit->Text = L"edit";
			this->edit->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->edit->UseVisualStyleBackColor = false;
			this->edit->Click += gcnew System::EventHandler(this, &MyForm::edit_Click);
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button4->BackColor = System::Drawing::SystemColors::Control;
			this->button4->Location = System::Drawing::Point(644, 0);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 6;
			this->button4->Text = L"paste on";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// openTexFileDialog
			// 
			this->openTexFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openTexFileDialog_FileOk);
			// 
			// pictureBoxDialog
			// 
			this->pictureBoxDialog->FileName = L"pictureBoxDialog";
			this->pictureBoxDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::pictureBoxDialog_FileOk);
			// 
			// multiselect
			// 
			this->multiselect->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->multiselect->Location = System::Drawing::Point(134, 25);
			this->multiselect->Name = L"multiselect";
			this->multiselect->Size = System::Drawing::Size(50, 50);
			this->multiselect->TabIndex = 19;
			this->multiselect->Text = L"multiselect";
			this->multiselect->UseVisualStyleBackColor = false;
			this->multiselect->Click += gcnew System::EventHandler(this, &MyForm::multiselect_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(800, 624);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->menuStrip1);
			this->DoubleBuffered = true;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"OpenMesh_EX";
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void hkoglPanelControl1_Load(System::Object^  sender, System::EventArgs^  e)
	{
		//glfwInit();
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cout << "GLEW is not initialized!\n";
			return;
		}
		glEnable(GL_TEXTURE_2D);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_POINT_SMOOTH);
		//ResourcePath::shaderPath = "./Shader/" + ProjectName + "/";
		drawModelShader.Init();
		pickingShader.Init();
		pickingTexture.Init(windowWidth, windowHeight);

		drawPickingFaceShader.Init();	
	}
			 //畫
	private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{

		//glEnable(GL_COLOR_MATERIAL);
		//glClearColor(1.0, 1.0, 1.0, 1.0);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//point center;
		//center[0] = 0.0;
		//center[1] = 0.0;
		//center[2] = 0.0;
		//camera.setupGL(xf * center, 1.0);
		aspect = windowWidth * 1.0f / windowHeight;
		//std::cout << aspect << std::endl;
		glm::mat4 mvMat = meshWindowCam.GetViewMatrix()*meshWindowCam.GetModelMatrix();
		glm::mat4 pMat = meshWindowCam.GetProjectionMatrix(aspect);


		// write faceID+1 to framebuffer
		pickingTexture.Enable();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pickingShader.Enable();
		pickingShader.SetMVMat(value_ptr(mvMat));
		pickingShader.SetPMat(value_ptr(pMat));

		if (render_tex == false)
			model.Render();

		pickingShader.Disable();
		pickingTexture.Disable();


		// draw model
		glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawModelShader.Enable();
		glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(mvMat)));

		glm::mat4 RotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f + rotation), glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 ScaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f + scal, 1.0f + scal, 1.0f + scal));
		glm::mat4 TranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f + translat, 1.0f + translat, 1.0f + translat));
		//drawModelShader.SetWireColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		drawModelShader.SetFaceColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		drawModelShader.UseLighting(true);
		drawModelShader.DrawTexCoord(false);
		drawModelShader.DrawTexture(false);

		//drawModelShader.DrawWireframe(true);
		drawModelShader.SetNormalMat(normalMat);
		drawModelShader.SetMVMat(mvMat);
		drawModelShader.SetPMat(pMat);
		if (render_tex == false)
			model.Render();
		drawModelShader.Disable();

		if (selectionMode == 1 || selectionMode == 2) {
			drawPickingFaceShader.Enable();
			drawPickingFaceShader.SetMVMat(value_ptr(mvMat));
			drawPickingFaceShader.SetPMat(value_ptr(pMat));
			drawPickingFaceShader.SetTex();
			if (render_tex == false)
				model.RenderSelectedFace();
			drawPickingFaceShader.Disable();
		}
		
		if (light == false&&edit_mode==false)
		{
			drawModelShader.Enable();
			drawModelShader.SetFaceColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

			drawModelShader.DrawTexture(true);
			drawModelShader.UseLighting(true);
			glActiveTexture(GL_TEXTURE0);
            drawModelShader.SetUVRotMat(ScaleMat*RotateMat*TranslateMat);
			drawModelShader.SetNormalMat(normalMat);
			drawModelShader.SetMVMat(mvMat);
			drawModelShader.SetPMat(pMat);

			if (render_tex == false)
			{				
				for (int i = 0; i < model.model.mesh_tex.size() ; i++)
				{

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, id[i]);
					model.Render_mesh2(i);
				}		
			}
			drawModelShader.Disable();
		}
		if (render_tex == true)
		{
			drawModelShader.Enable();
			drawModelShader.SetFaceColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

			drawModelShader.DrawTexCoord(true);
			drawModelShader.DrawTexture(true);
			drawModelShader.UseLighting(true);
			drawModelShader.SetUVRotMat(ScaleMat*RotateMat*TranslateMat);

			drawModelShader.SetNormalMat(normalMat);
			drawModelShader.SetMVMat(mvMat);
			drawModelShader.SetPMat(pMat);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, id[model.mesh_id]);
			model.Render_TexCoord();
			model.Render_TexCoord2();

			
			drawModelShader.Disable();
		}
		
		/*if (selectionMode == 3)
		{
			if (updateFlag)
			{
				float depthValue = 0;
				int windowX = currentMouseX;
				int windowY = windowHeight - currentMouseY;
				glReadPixels(windowX, windowY, 2, 1.5, GL_DEPTH_COMPONENT, GL_FLOAT, &depthValue);

				GLint _viewport[4];
				glGetIntegerv(GL_VIEWPORT, _viewport);
				glm::vec4 viewport(_viewport[0], _viewport[1], _viewport[2], _viewport[3]);
				glm::vec3 windowPos(windowX, windowY, depthValue);
				glm::vec3 wp = glm::unProject(windowPos, mvMat, pMat, viewport);
				model.FindClosestPoint(currentFaceID - 1, wp, worldPos);

				updateFlag = false;
				//hkoglPanelControl1->Invalidate();
			}*/
			/*
				Using OpenGL 1.1 to draw point
			*/
			/*glPushMatrix();
			glPushAttrib(GL_POINT_BIT);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glMultMatrixf(glm::value_ptr(pMat));

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glMultMatrixf(glm::value_ptr(mvMat));

				glPointSize(15.0f);
				glColor3f(1.0, 0.0, 1.0);
				glBegin(GL_POINTS);
				glVertex3fv(glm::value_ptr(worldPos));
				glEnd();
			glPopAttrib();
			glPopMatrix();*/


			/*glBindBuffer(GL_ARRAY_BUFFER, vboPoint);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), glm::value_ptr(worldPos), GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			glm::vec4 pointColor(1.0, 0.0, 1.0, 1.0);
			drawPointShader.Enable();
			drawPointShader.SetMVMat(mvMat);
			drawPointShader.SetPMat(pMat);
			drawPointShader.SetPointColor(pointColor);
			drawPointShader.SetPointSize(15.0);

			glDrawArrays(GL_POINTS, 0, 1);

			drawPointShader.Disable();

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//hkoglPanelControl1->Invalidate();
		}*/
		//glUseProgram(0);
		/*glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixd((double *)xf);
		if (mesh != NULL)
			mesh->Render_SolidWireframe();
		glPopMatrix();*/
	}
			 //滑鼠按下去
	private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Right ||
			e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			SelectionHandler(e->X, e->Y);
			//std::cout << "x="<< e->X<<"  y="<< e->Y << std::endl;
			//std::cout << "MouseButtons_Right" << std::endl;
			//hkoglPanelControl1->Invalidate();
			//meshWindowCam.mousePressEvent( 3, e->X, e->Y);
			/*point center;
			Mouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);*/
		}
		else if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			meshWindowCam.mouseEvents(0, 1, e->X, e->Y);
			//meshWindowCam.mouseMoveEvent(e->X, e->Y);
			//SelectionHandler(e->X, e->Y);
			//std::cout << "x=" << e->X << "  y=" << e->Y << std::endl;
			//hkoglPanelControl1->Invalidate();
			//std::cout << "MouseButtons_Right" << std::endl;
			//hkoglPanelControl1->Invalidate();
			//meshWindowCam.mousePressEvent( 3, e->X, e->Y);
			/*point center;
			Mouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);*/
		}
	}
			 //滑鼠轉動
	private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			//meshWindowCam.mouseEvents(0, 1, e->X, e->Y);
			meshWindowCam.mouseMoveEvent(e->X, e->Y);
			/*point center;
			Mouse_State = Mouse::ROTATE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);*/
			hkoglPanelControl1->Invalidate();
		}

		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			SelectionHandler(e->X, e->Y);
			/*point center;
			Mouse_State = Mouse::MOVEXY;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);*/
			hkoglPanelControl1->Invalidate();
		}
	}
			 //滑鼠滾輪
	private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Delta < 0)
		{
			meshWindowCam.mouseEvents(3, 3, e->X, e->Y);
			/*point center;
			Mouse_State = Mouse::WHEELDOWN;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);*/
			hkoglPanelControl1->Invalidate();
		}
		else
		{
			meshWindowCam.mouseEvents(4, 4, e->X, e->Y);
			/*point center;
			Mouse_State = Mouse::WHEELUP;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);*/
			hkoglPanelControl1->Invalidate();
		}
	}
	private: System::Void hkoglPanelControl1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^ e)
	{
		meshWindowCam.keyEvents(e->KeyChar);
		if (e->KeyChar == 'w' || e->KeyChar == 'W') {
			meshWindowCam.keyEvents(e->KeyChar);

			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
		else if (e->KeyChar == 'a' || e->KeyChar == 'A') {
			meshWindowCam.keyEvents(e->KeyChar);

			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
		else if (e->KeyChar == 's' || e->KeyChar == 'S') {
			meshWindowCam.keyEvents(e->KeyChar);

			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
		else if (e->KeyChar == 'd' || e->KeyChar == 'D') {
			meshWindowCam.keyEvents(e->KeyChar);

			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
		else if (e->KeyChar == '-') {
			meshWindowCam.keyEvents(e->KeyChar);

			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
		else if (e->KeyChar == '+') {
			meshWindowCam.keyEvents(e->KeyChar);

			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
		else if (e->KeyChar == '1') {
			selectionMode = 1;
			//std::cout << "selectionMode=" << selectionMode << std::endl;
			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
		else if (e->KeyChar == '2') {
			selectionMode = 2;
			//std::cout << "selectionMode=" << selectionMode << std::endl;
			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
		else if (e->KeyChar == '3') {
			selectionMode = 3;
			//std::cout << "selectionMode=" << selectionMode << std::endl;
			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}	
		else if (e->KeyChar == '4') {
			if (model.other_increase == 0)
				model.other_increase = 1;
			else if (model.other_increase == 1)
				model.other_increase = 0;
			//std::cout << "selectionMode=" << selectionMode << std::endl;
			hkoglPanelControl1->Invalidate();
			//e.Handled = true;
		}
	}
			 //按下load model選單
	private: System::Void loadModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openModelDialog->Filter = "Model(*.obj)|*obj";
		openModelDialog->Multiselect = false;
		openModelDialog->ShowDialog();
	}
			 //載入檔案
	private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(openModelDialog->FileName, filename);

		//if (mesh != NULL)
			//delete mesh;
		//mesh = new Tri_Mesh;
		if (model.Init(filename))
		{
			std::cout << "Load Model" << filename << std::endl;
		}
		else
		{
			//puts("Load Model Failed");
			std::cout << "Load Model Failed" << std::endl;
		}
		//if (ReadFile(filename, mesh))
			//std::cout << filename << std::endl;

		hkoglPanelControl1->Invalidate();
	}
			 //按下save model選單
	private: System::Void saveModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//saveModelDialog->Filter = "Model(*.obj)|*obj";
		saveModelDialog->Filter = "文字檔案(*.txt)|*.txt";
		saveModelDialog->ShowDialog();
	}
			 //輸出檔案
	private: System::Void saveModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(saveModelDialog->FileName, filename);			

		std::fstream outFile;
		outFile.open(filename, std::ios_base::trunc | std::ios_base::out);
		if (!outFile)
		{
			std::cout << "Files is not opened!" << std::endl;
			exit(1);
		}

		for (int i = 0; i < model.model.mesh_tex.size(); i++)
		{
			outFile << "c" << "\n";
			outFile << "f" << " ";
			for (MyMesh::FaceIter f_it = model.model.mesh_tex[i].faces_begin(); f_it != model.model.mesh_tex[i].faces_end(); ++f_it)
			{
				for (MyMesh::FaceVertexIter fv_it = model.model.mesh_tex[i].fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
				{

					MyMesh::Point p1 = model.model.mesh_tex[i].point(*fv_it);
					//std::cout << "p1: " << p1 << std::endl;
					++fv_it;
					MyMesh::Point p2 = model.model.mesh_tex[i].point(*fv_it);
					//std::cout << "p2: " << p2 << std::endl;
					++fv_it;
					MyMesh::Point p3 = model.model.mesh_tex[i].point(*fv_it);
					//std::cout << "p3: " << p3 << std::endl;
					int FaceId = model.model.mesh.FindFace(p1, p2, p3);
					//std::cout << "FaceId: " << FaceId << std::endl;
					outFile << FaceId <<" ";
				}
			}
			outFile  << "\n";
			//std::cout << "pass 1: "<< model.model.mesh_tex.size() << std::endl;
			outFile << "t" << " ";
			for (int j = 0; j < model.mesh_record[i].x.size(); j++)
			{
				outFile << model.mesh_record[i].x[j]<< " ";
				//std::cout << "x: " << model.mesh_record[i].x[j] << std::endl;
				outFile << model.mesh_record[i].y[j]<< " ";
				//std::cout << "y: " << model.mesh_record[i].y[j] << std::endl;
			}
			outFile << "\n";
			//std::cout << "pass 2: "<< model.mesh_record[i].x.size() << std::endl;
			/*outFile << i<<"\n";
			std::cout << "pass 3" << std::endl;*/
			outFile << "a" << "\n";
		}

		outFile.close();
		//model.End(filename);
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void SelectionHandler(unsigned int x, unsigned int y)
	{
		faceID = pickingTexture.ReadTexture(x, windowHeight - y - 1);
		//std::cout << "x=" << x << "  y=" << y << std::endl;
		//std::cout << "faceID="<<faceID << std::endl;
		//if (faceID != 0)
			//{
			//	currentFaceID = faceID;
			//}
		//std::cout << "selectionMode=" << selectionMode << std::endl;
			//if (selectionMode == ADD_FACE)
		if (selectionMode == 1)
		{
			if (faceID != 0)
			{
				model.AddSelectedFace(faceID - 1);
				//std::cout << "AddSelectedFace_finish" << std::endl;
			}
			hkoglPanelControl1->Invalidate();
		}
		else if (selectionMode == 2)
		{
			if (faceID != 0)
			{
				model.DeleteSelectedFace(faceID - 1);
				//std::cout << "DeleteSelectedFace_finish" << std::endl;
			}
			hkoglPanelControl1->Invalidate();
		}
		else if (selectionMode == 3)
		{
			currentMouseX = x;
			currentMouseY = y;
			updateFlag = true;
			hkoglPanelControl1->Invalidate();
		}
	}

	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void hkoglPanelControl1_Resize(System::Object^  sender, System::EventArgs^  e) {
		windowHeight = this->Size.Height - 60;
		windowWidth = this->Size.Width;
		glewInit();
		pickingTexture.Init(windowWidth, windowHeight);
		hkoglPanelControl1->Invalidate();

	}

	


	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		openFileDialog1->Filter = "Image Files(*.PNG;*.JPG;*.GIF)|*.PNG;*.JPG;*.GIF|All files (*.*)|*.*";		
		openFileDialog1->ShowDialog();
	}
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

		std::string filename;

		MarshalString(openFileDialog1->FileName, filename);

		std::cout << filename << std::endl;
		const char * file=filename.c_str();
		int image_width;
		int image_height;
		int imgcor;
		id.push_back(0);
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(file, &image_width, &image_height, &imgcor, 0);
		glGenTextures(1, &id[id.size()-1]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id[id.size() - 1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateMipmap(GL_TEXTURE_2D);
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		stbi_image_free(bytes);
		glBindTexture(GL_TEXTURE_2D, 0);
	
		model.create_mesh();
	
		textBox1->Text = "" + model.model.mesh_tex.size() ;	
		this->pictureBox1->Image = System::Drawing::Image::FromFile(openFileDialog1->FileName);
		int now = model.mesh_id;	
		this->pic_init = gcnew PictureBox;
		this->pic_init->Name = "" + (now);
		this->pic_init->Tag = id.size() - 1;
		this->pic_init->Location = Point(10, 20 + 1 * ((id.size() - 1) * 120));
		this->pic_init->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
		this->pic_init->Size = System::Drawing::Size(100, 100);
		this->pic_init->Image = System::Drawing::Image::FromFile(openFileDialog1->FileName);
		this->pic_init->Click += gcnew System::EventHandler(this, &MyForm::pic_Click);
		groupBox2->Controls->Add(this->pic_init);
		/*this->pictureBox1 = gcnew PictureBox;
		this->pictureBox1->Name = ""+ (now);
		this->pictureBox1->Tag = id.size()-1;
		this->pictureBox1->Location = Point(10, 20+1* ((id.size()-1)*120));
		this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
		this->pictureBox1->Size = System::Drawing::Size(100, 100);
		this->pictureBox1->Image = System::Drawing::Image::FromFile(openFileDialog1->FileName);
		this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
		groupBox2->Controls->Add(this->pictureBox1);*/
		std::cout << "create FINISH" << std::endl;
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

		numericUpDown1->Minimum = 0;
		numericUpDown1->Maximum = model.model.mesh_tex.size()-1;
		model.select_mesh((int)(numericUpDown1->Value));
		hkoglPanelControl1->Invalidate();
	}



	private: System::Void edit_Click(System::Object^  sender, System::EventArgs^  e) {

		if (edit_mode == false)
		{
			edit_mode = true;
			model.edit = true;
			model.edit_mode = true;
			model.face_num();
		}
		else if (edit_mode == true)
		{
			edit_mode = false;
			model.edit = false;
			model.edit_mode = false;
			model.edit_num = 1;
			model.boundary.clear();
			model.origin_face_num = 0;
		}
		hkoglPanelControl1->Invalidate();
	}


	private: System::Void zoom_in_Click(System::Object^  sender, System::EventArgs^  e) {
		scal += 1.0f;
		hkoglPanelControl1->Invalidate();

	}
	private: System::Void zoom_out_Click(System::Object^  sender, System::EventArgs^  e) {
		scal -= 1.0f;
		hkoglPanelControl1->Invalidate();

	}
	private: System::Void move_right_Click(System::Object^  sender, System::EventArgs^  e) {
		translat -= 0.1f;
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void move_left_Click(System::Object^  sender, System::EventArgs^  e) {
		translat += 0.1f;
		hkoglPanelControl1->Invalidate();
	}

	private: System::Void rotate_Click(System::Object^  sender, System::EventArgs^  e) {
		rotation += 5.0f;
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void mesh_zoom_in_Click(System::Object^  sender, System::EventArgs^  e) {
		model.increase_face();
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void mesh_zoom_out_Click(System::Object^  sender, System::EventArgs^  e) {
		model.decrease_face();
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		//edit_num = 2;
		model.edit_num = 2;
		hkoglPanelControl1->Invalidate();

	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

		//edit_num = 3;
		model.edit_num = 3;
		model.other_mesh_increase();
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

		if (checkBox1->Checked)
		{
			render_tex = true;
		}
		else
		{
			render_tex = false;
		}
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		if (faceID != 0 && selectionMode == 1)
		{
			model.AddSelectedFacefinished();
			light = false;				
		}
		
		hkoglPanelControl1->Invalidate();
	}

	private: System::Void pic_Click(System::Object^  sender, System::EventArgs^  e) {

		pictureBoxDialog->Filter = "Image Files(*.PNG;*.JPG;*.GIF)|*.PNG;*.JPG;*.GIF|All files (*.*)|*.*";
		pictureBoxDialog->ShowDialog();
		/*std::string num;
		MarshalString(pic->Name, num);
		num2 = stoi(num);
		std::cout << num << std::endl;*/
	}
		 
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {

		///*pictureBoxDialog->Filter = "Image Files(*.PNG;*.JPG;*.GIF)|*.PNG;*.JPG;*.GIF|All files (*.*)|*.*";
		//pictureBoxDialog->ShowDialog();*/
		//std::string num;
		//MarshalString(pictureBox1->Name, num);
		///*int num2 = stoi(num);*/
		//std::cout << num << std::endl;
	}
	private: System::Void pictureBoxDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		std::string filename;

		MarshalString(pictureBoxDialog->FileName, filename);

		std::cout << filename << std::endl;
		const char * file = filename.c_str();
		int image_width;
		int image_height;
		int imgcor;
		id.push_back(0);
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(file, &image_width, &image_height, &imgcor, 0);
		glGenTextures(1, &id[model.mesh_id]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id[model.mesh_id]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateMipmap(GL_TEXTURE_2D);
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		stbi_image_free(bytes);
		glBindTexture(GL_TEXTURE_2D, 0);

		textBox1->Text = "" + model.model.mesh_tex.size();

		this->pictureBox1->Image = System::Drawing::Image::FromFile(pictureBoxDialog->FileName);
		this->pic_init->Image = System::Drawing::Image::FromFile(pictureBoxDialog->FileName);
		//pic_init->Controls->Remove();
		hkoglPanelControl1->Invalidate();
	}
	private: System::Void reset_Click(System::Object^  sender, System::EventArgs^  e) {
		rotation = 0.0f; 
		scal = 0.0f; 
		translat = 0.0f;
	}
	private: System::Void loadTextureToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		openTexFileDialog->Filter = "文字檔案(*.txt)|*.txt";
		openTexFileDialog->Multiselect = false;
		openTexFileDialog->ShowDialog();
	}
	private: System::Void openTexFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		std::string filename;
		MarshalString(openTexFileDialog->FileName, filename);
		std::ifstream mytxt;
		char buffer[500000] = { 0 };
		char create[] = "c", add[] = "a", faceid[] = "f", texcoord[] = "t";
		std::string Create = create, Add = add, FaceId=faceid,TexCoord = texcoord;
		mytxt.open(filename);
		bool f_flag = false, t_flag = false;
		int time = 0;
		if (!mytxt.is_open()) 
		{
			std::cout << "Failed to open file.\n";
		}
		else 
		{

			while (!mytxt.eof()) 
			{
				mytxt.getline(buffer, sizeof(buffer));
				//std::cout << "sizeof(buffer) " << sizeof(buffer) << std::endl;
				std::string tmp = buffer;
				std::vector<std::string> ret = model.split(tmp, ' ');
				//std::cout << tmp << "\n";
				if (tmp == Create)
				{
					button1_Click(sender, e);

				}
				if (tmp == FaceId)
				{
					button1_Click(sender, e);

				}
				for (int i=0;i< ret.size();i++)
				{
					if (f_flag == true&& ret[i]!= TexCoord)
					{
						model.AddSelectedFace((unsigned int)std::stoi(ret[i]));
						//std::cout << std::stoi(ret[i]) << '\n';
					}
					else if (t_flag == true&&ret[i]!= Add)
					{
						time++;
						if (time % 2 == 1)
						{
													
						}
						else if (time % 2 == 0)
						{
							model.load_tex_info_vector(std::stof(ret[i - 1]), std::stof(ret[i]));
							//std::cout << ret[i-1] <<" "<<ret[i] << '\n';
						}						
					}
					else if (ret[i] == FaceId)
					{
						f_flag = true;
						t_flag = false;
					}
					else if (ret[i] == TexCoord)
					{
						f_flag = false;
						t_flag = true;
					}
					else if (ret[i] == Add)
					{
						f_flag = false;
						t_flag = false;
					}
				}
				if (tmp == Add)
				{
					model.edit_num = 3;
					model.AddSelectedFacefinished();
					
					model.load_tex_info();
					model.edit_num = 1;
					light = false;
				}
				
				time = 0;
			}
			mytxt.close();
		}
		std::cout << "load texture finish"<<std::endl;
		hkoglPanelControl1->Invalidate();
	}

	private: System::Void multiselect_Click(System::Object^  sender, System::EventArgs^  e) {
		if (model.multi_select == true)
			model.multi_select = false;
		else if (model.multi_select == false)
			model.multi_select = true;
	}
};
}
