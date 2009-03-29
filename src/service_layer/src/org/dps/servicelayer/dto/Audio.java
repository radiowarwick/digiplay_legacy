package org.dps.servicelayer.dto;

import javax.annotation.Generated;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name="audio")
public class Audio extends Audit {
	
	@Column(name="audio_id")
	@Id
	@Generated(value="sequence")
	private Long audioID;
	
	//FileID - New Object
	
	@Column(name="md5")
	private String md5;
	
	@Column(name="length_smpl")
	private Integer sampleLength;
	
	@Column(name="start_smpl")
	private Integer sampleStart;
	
	@Column(name="end_smpl")
	private Integer sampleEnd;
	
	@Column(name="intro_smpl")
	private Integer sampleIntro;
	
	@Column(name="extro_smpl")
	private Integer sampleExtro;
	
	//AudioTypeID object
	//Createor object
	
	@Column(name="import_date")
	private Integer importDate;
	
	@Column(name="title")
	private String title;
	
	@Column(name="sustainer")
	private Boolean sustainer;
	
	@Column(name="flagged")
	private Boolean flagged;
	
	@Column(name="censor")
	private Boolean censor;
	
	@Column(name="filetype")
	private String fileType;
	
	public String toString() {
		return audioID + ":" + title;
	}
	
	/**
	 * @return the audioID
	 */
	public Long getAudioID() {
		return audioID;
	}
	/**
	 * @param audioID the audioID to set
	 */
	public void setAudioID(Long audioID) {
		this.audioID = audioID;
	}
	/**
	 * @return the md5
	 */
	public String getMd5() {
		return md5;
	}
	/**
	 * @param md5 the md5 to set
	 */
	public void setMd5(String md5) {
		this.md5 = md5;
	}
	/**
	 * @return the sampleLength
	 */
	public Integer getSampleLength() {
		return sampleLength;
	}
	/**
	 * @param sampleLength the sampleLength to set
	 */
	public void setSampleLength(Integer sampleLength) {
		this.sampleLength = sampleLength;
	}
	/**
	 * @return the sampleStart
	 */
	public Integer getSampleStart() {
		return sampleStart;
	}
	/**
	 * @param sampleStart the sampleStart to set
	 */
	public void setSampleStart(Integer sampleStart) {
		this.sampleStart = sampleStart;
	}
	/**
	 * @return the sampleEnd
	 */
	public Integer getSampleEnd() {
		return sampleEnd;
	}
	/**
	 * @param sampleEnd the sampleEnd to set
	 */
	public void setSampleEnd(Integer sampleEnd) {
		this.sampleEnd = sampleEnd;
	}
	/**
	 * @return the sampleIntro
	 */
	public Integer getSampleIntro() {
		return sampleIntro;
	}
	/**
	 * @param sampleIntro the sampleIntro to set
	 */
	public void setSampleIntro(Integer sampleIntro) {
		this.sampleIntro = sampleIntro;
	}
	/**
	 * @return the sampleExtro
	 */
	public Integer getSampleExtro() {
		return sampleExtro;
	}
	/**
	 * @param sampleExtro the sampleExtro to set
	 */
	public void setSampleExtro(Integer sampleExtro) {
		this.sampleExtro = sampleExtro;
	}
	/**
	 * @return the importDate
	 */
	public Integer getImportDate() {
		return importDate;
	}
	/**
	 * @param importDate the importDate to set
	 */
	public void setImportDate(Integer importDate) {
		this.importDate = importDate;
	}
	/**
	 * @return the title
	 */
	public String getTitle() {
		return title;
	}
	/**
	 * @param title the title to set
	 */
	public void setTitle(String title) {
		this.title = title;
	}
	/**
	 * @return the sustainer
	 */
	public Boolean getSustainer() {
		return sustainer;
	}
	/**
	 * @param sustainer the sustainer to set
	 */
	public void setSustainer(Boolean sustainer) {
		this.sustainer = sustainer;
	}
	/**
	 * @return the flagged
	 */
	public Boolean getFlagged() {
		return flagged;
	}
	/**
	 * @param flagged the flagged to set
	 */
	public void setFlagged(Boolean flagged) {
		this.flagged = flagged;
	}
	/**
	 * @return the censor
	 */
	public Boolean getCensor() {
		return censor;
	}
	/**
	 * @param censor the censor to set
	 */
	public void setCensor(Boolean censor) {
		this.censor = censor;
	}
	/**
	 * @return the fileType
	 */
	public String getFileType() {
		return fileType;
	}
	/**
	 * @param fileType the fileType to set
	 */
	public void setFileType(String fileType) {
		this.fileType = fileType;
	}

}
