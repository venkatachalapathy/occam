/*
 * ocReport.h - generate reports from model data.
 * an ocReport object holds a list of models, and a list of attributes to print.
 * The collection can be sorted and/or filtered, and the resulting models printed.
 */
 
#ifndef OCREPORT_H
#define OCREPORT_H
#include <stdio.h>

class ocReport {
public:
	enum SortDir {ASCENDING, DESCENDING};
	ocReport(class ocManagerBase *mgr);
	~ocReport();
	
	//-- Add a model to the list of models. The model is added at the end. Run sort() after
	//-- all models are added to sort them.
	void addModel(class ocModel *model);
	
	//-- Set the attributes to report. This is a comma-separated list, from those in
	//-- ocCore.h
	void setAttributes(const char *attrlist);
	
	//-- One-time sort of models, based on the given attribute.
	void sort(const char *attr, SortDir dir);
	
	//-- Static function others can use to sort model lists
	static void sort(class ocModel** models, long modelCount,
		const char *attr, SortDir dir);
	
	
	//-- Print a tabular output format.
	void print(FILE *fd);
	void print(int fnum);	// use a file number instead of FILE*
	//-- Set report separator type: 1=tab, 2=comma, 3=space filled
	void setSeparator(int sep) { separator = sep; }
	
	//-- HTML Mode - changes formatting
	static bool isHTMLMode() {return htmlMode; }
	static void setHTMLMode(bool mode) { htmlMode = mode; }

	//-- Print residual table
	void printResiduals(FILE *fd, ocModel *model);
	
protected:
	static bool htmlMode;
	class ocManagerBase *manager;
	ocModel **models;
	char **attrs;
	long modelCount, maxModelCount;
	long attrCount;
	int separator;
};

#endif