package org.dps.servicelayer.common;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

import org.dps.servicelayer.Constants;

@XmlAccessorType(XmlAccessType.FIELD)
public class ResultSetDetails {
	
	@XmlElement(required = true, name = "sortByColumn")
	@XmlElementWrapper(name = "sortByColumns", required = true)
	private List<String> sortByColumns = new ArrayList<String>();
	
	@XmlElement(required = true)
	private Integer resultsPerPage = Constants.DEFAULT_RESULTS_PER_PAGE;
	
	@XmlElement(required = true)
	private Integer pageNum = Integer.valueOf(0);
	
	@XmlElement(required = true)
	private boolean invertSearch = false;
	
	@XmlElement(required = true)
	private Integer numResults = Integer.valueOf(0);
	
	@XmlElement(required = true)
	private Integer numPages = Integer.valueOf(0);
	
	public ResultSetDetails() { }
	
	public ResultSetDetails(ResultSetControl control) {
		if(control != null) {
			if(control.getSortByColumns() != null) {
				this.sortByColumns.addAll(control.getSortByColumns());
			}
			if(control.getResultsPerPage() != null) {
				this.resultsPerPage = control.getResultsPerPage();
			}
			if(control.getPageNum() != null) {
				this.pageNum = control.getPageNum();
			}
			this.invertSearch = control.isInvertSearch();
		}
	}
	public List<String> getSortByColumns() {
		return Collections.unmodifiableList(sortByColumns);
	}
	public void setSortByColumns(List<String> sortByColumns_) {
		sortByColumns = sortByColumns_;
	}
	public void addSortByColumn(String column) {
		sortByColumns.add(column);
	}
	public void removeSortByColumn(String column) {
		sortByColumns.remove(column);
	}
	public void clearSortByColumn(String column) {
		sortByColumns.clear();
	}
	public Integer getResultsPerPage() {
		return resultsPerPage;
	}
	public void setResultsPerPage(Integer resultsPerPage_) {
		resultsPerPage = resultsPerPage_;
	}
	public Integer getPageNum() {
		return pageNum;
	}
	public void setPageNum(Integer pageNum_) {
		pageNum = pageNum_;
	}
	public boolean isInvertSearch() {
		return invertSearch;
	}
	public void setInvertSearch(boolean invertSearch_) {
		invertSearch = invertSearch_;
	}
	public Integer getNumResults() {
		return numResults;
	}
	public void setNumResults(Integer numResults_) {
		numResults = numResults_;
	}
	public Integer getNumPages() {
		return numPages;
	}
	public void setNumPages(Integer numPages_) {
		numPages = numPages_;
	}
	
}
