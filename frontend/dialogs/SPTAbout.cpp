#include "SPTAbout.hpp"

#include <widgets/OBSBasic.hpp>
#include <utility/RemoteTextThread.hpp>

#include <qt-wrappers.hpp>

#include <json11.hpp>

#include "moc_SPTAbout.cpp"

using namespace json11;

SPTAbout::SPTAbout(QWidget *parent) : QDialog(parent), ui(new Ui::SPTAbout), about(nullptr)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	ui->setupUi(this);
	this->setWindowTitle("About SPECTRUM Live Studio");
	auto showOBSAbout = [this]() {
		if (this->about)
			this->about->close();
		this->about = new OBSAbout(this);
		this->about->show();
		this->about->setAttribute(Qt::WA_DeleteOnClose, true);
	};
	connect(ui->btnAboutOBS, &QPushButton::clicked, this, showOBSAbout);
}

