#ifndef SCANEXPERIMENTCONFIG_H
#define SCANEXPERIMENTCONFIG_H

#include "gradienthiddenwidget.h"
#include "qgridlayout.h"
#include "button.h"
#include "qmessagebox.h"

class ScanExperimentConfig : public GradientHiddenWidget
{
    Q_OBJECT
public:
    enum ExperimentType {Proliferation,Scratch,Organoid,PC,Invasion,Morphology,Transfection,Empty};
    explicit ScanExperimentConfig(QWidget *parent = nullptr);
    bool checkExperimentType();
private:
    Button * mProliferation; // 细胞增殖
    Button * mScratch; // 划痕
    Button * mOrganoid;// 类器官
    Button * mPC;// 药效和细胞毒性 Pharmacodynamics and Cytotoxicity
    Button * mInvasion;// 侵袭
    Button * mMorphology;// 形态学
    Button * mTransfection;// 转染
    QLabel * mCurrentExper;
    ExperimentType type = Empty;
private:
    void onProliferation();
    void onScratch();
    void onOrganoid();
    void onPC();
    void onInvasion();
    void onMorphology();
    void onTransfection();
signals:

};

#endif // SCANEXPERIMENTCONFIG_H
