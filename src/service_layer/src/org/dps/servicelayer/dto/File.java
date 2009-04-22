package org.dps.servicelayer.dto;

import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Inheritance;
import javax.persistence.InheritanceType;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToMany;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.OneToOne;
import javax.persistence.PrePersist;
import javax.persistence.Table;

import org.hibernate.annotations.Generated;
import org.hibernate.annotations.GenerationTime;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Entity
@Table(name="file")
@Inheritance(strategy=InheritanceType.JOINED)
public class File extends Audit {
	
	@Column(name="file_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long fileID;
	
	@ManyToOne
	@JoinColumn(name="parent")
	private File parent;
	
	@OneToMany
	@JoinColumn(name="parent")
	private Set<File> children = new HashSet<File>();
	
	@Column(name="filename")
	private String filename;
	
	@Column(name="owner_id")
	private Integer ownerID;
	
	@Column(name="group_id")
	private Integer groupID;
	
	@Column(name="entity_type")
	private Integer entityType;
	
	@Column(name="user_r")
	private Boolean userRead;
	
	@Column(name="user_w")
	private Boolean userWrite;
	
	@Column(name="user_x")
	private Boolean userExecute;
	
	@Column(name="group_r")
	private Boolean groupRead;
	
	@Column(name="group_w")
	private Boolean groupWrite;
	
	@Column(name="group_x")
	private Boolean groupExecute;
	
	@Column(name="all_r")
	private Boolean allRead;
	
	@Column(name="all_w")
	private Boolean allWrite;
	
	@Column(name="all_x")
	private Boolean allExecute;
	
	@Column(name="created",updatable = false, insertable = true)
	private Long created = new Date().getTime();
	
	public String toString() {
		return fileID + ":" + filename;
	}

	/**
	 * @return the fileID
	 */
	public Long getFileID() {
		return fileID;
	}

	/**
	 * @param fileID the fileID to set
	 */
	public void setFileID(Long fileID) {
		this.fileID = fileID;
	}

	/**
	 * @return the parent
	 */
	public File getParent() {
		return parent;
	}

	/**
	 * @param parent the parent to set
	 */
	public void setParent(File parent) {
		this.parent = parent;
	}

	/**
	 * @return the children
	 */
	public Set<File> getChildren() {
		return children;
	}

	/**
	 * @param children the children to set
	 */
	public void setChildren(Set<File> children) {
		this.children = children;
	}

	/**
	 * @return the name
	 */
	public String getFileame() {
		return filename;
	}

	/**
	 * @param name the name to set
	 */
	public void setFilename(String filename) {
		this.filename = filename;
	}

	/**
	 * @return the ownerID
	 */
	public Integer getOwnerID() {
		return ownerID;
	}

	/**
	 * @param ownerID the ownerID to set
	 */
	public void setOwnerID(Integer ownerID) {
		this.ownerID = ownerID;
	}

	/**
	 * @return the groupID
	 */
	public Integer getGroupID() {
		return groupID;
	}

	/**
	 * @param groupID the groupID to set
	 */
	public void setGroupID(Integer groupID) {
		this.groupID = groupID;
	}

	/**
	 * @return the entityType
	 */
	public Integer getEntityType() {
		return entityType;
	}

	/**
	 * @param entityType the entityType to set
	 */
	public void setEntityType(Integer entityType) {
		this.entityType = entityType;
	}

	/**
	 * @return the userRead
	 */
	public Boolean getUserRead() {
		return userRead;
	}

	/**
	 * @param userRead the userRead to set
	 */
	public void setUserRead(Boolean userRead) {
		this.userRead = userRead;
	}

	/**
	 * @return the userWrite
	 */
	public Boolean getUserWrite() {
		return userWrite;
	}

	/**
	 * @param userWrite the userWrite to set
	 */
	public void setUserWrite(Boolean userWrite) {
		this.userWrite = userWrite;
	}

	/**
	 * @return the userExecute
	 */
	public Boolean getUserExecute() {
		return userExecute;
	}

	/**
	 * @param userExecute the userExecute to set
	 */
	public void setUserExecute(Boolean userExecute) {
		this.userExecute = userExecute;
	}

	/**
	 * @return the groupRead
	 */
	public Boolean getGroupRead() {
		return groupRead;
	}

	/**
	 * @param groupRead the groupRead to set
	 */
	public void setGroupRead(Boolean groupRead) {
		this.groupRead = groupRead;
	}

	/**
	 * @return the groupWrite
	 */
	public Boolean getGroupWrite() {
		return groupWrite;
	}

	/**
	 * @param groupWrite the groupWrite to set
	 */
	public void setGroupWrite(Boolean groupWrite) {
		this.groupWrite = groupWrite;
	}

	/**
	 * @return the groupExecute
	 */
	public Boolean getGroupExecute() {
		return groupExecute;
	}

	/**
	 * @param groupExecute the groupExecute to set
	 */
	public void setGroupExecute(Boolean groupExecute) {
		this.groupExecute = groupExecute;
	}

	/**
	 * @return the allRead
	 */
	public Boolean getAllRead() {
		return allRead;
	}

	/**
	 * @param allRead the allRead to set
	 */
	public void setAllRead(Boolean allRead) {
		this.allRead = allRead;
	}

	/**
	 * @return the allWrite
	 */
	public Boolean getAllWrite() {
		return allWrite;
	}

	/**
	 * @param allWrite the allWrite to set
	 */
	public void setAllWrite(Boolean allWrite) {
		this.allWrite = allWrite;
	}

	/**
	 * @return the allExecute
	 */
	public Boolean getAllExecute() {
		return allExecute;
	}

	/**
	 * @param allExecute the allExecute to set
	 */
	public void setAllExecute(Boolean allExecute) {
		this.allExecute = allExecute;
	}

	/**
	 * @return the created
	 */
	public Long getCreated() {
		return created;
	}

	/**
	 * @param created the created to set
	 */
	public void setCreated(Long created) {
		this.created = created;
	}
	
}
