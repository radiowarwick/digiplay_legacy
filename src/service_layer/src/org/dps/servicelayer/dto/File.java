package org.dps.servicelayer.dto;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.HashSet;
import java.util.Set;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Inheritance;
import javax.persistence.InheritanceType;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlTransient;

import org.dps.servicelayer.common.SummaryItem;
import org.hibernate.annotations.Generated;
import org.hibernate.annotations.GenerationTime;

@Entity
@Table(name="file")
@Inheritance(strategy=InheritanceType.JOINED)
@XmlAccessorType(XmlAccessType.PROPERTY)
public class File extends Audit {
	
	@Column(name="file_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long fileID;
	
	@ManyToOne
	@JoinColumn(name="parent", nullable=false)
	private File parent;
	
	@Column(name="parent", updatable = false, insertable = false)
	private Long parentID;
	
	@OneToMany
	@JoinColumn(name="parent")
	private Set<File> children = new HashSet<File>();
	
	@Column(name="filename")
	private String filename;

	@ManyToOne
	@JoinColumn(name="group_id")
	private Group ownerGroup = new Group();
	
	@ManyToOne
	@JoinColumn(name="owner_id")
	private User owner = new User();
	
	@Column(name="entity_type", updatable = false)
	private Integer entityType = Constants.FILE_TYPE_DIR;
	
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
	@Generated(GenerationTime.NEVER)
	private Calendar created = new GregorianCalendar();

	public File() {
		
	}
	
	public File(Integer entityType) {
		
	}
	/**
	 * @return the fileID
	 */
	@XmlElement(required = true)
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
	@XmlTransient
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
	@XmlTransient
	protected Set<File> getChildren() {
		return children;
	}
	/**
	 * @param children the children to set
	 */
	protected void setChildren(Set<File> children) {
		this.children = children;
	}
	public void addChild(File file) {
		file.setParent(this);
		children.add(file);
	}
	public File deleteChild(File file) {
		file.setParent(null);
		children.remove(file);
		return file;
	}

	/**
	 * @return the name
	 */
	@XmlElement(required = true)
	public String getFilename() {
		return filename;
	}
	/**
	 * @param name the name to set
	 */
	public void setFilename(String filename) {
		this.filename = filename;
	}

	/**
	 * @return the entityType
	 */
	@XmlElement(required = true)
	public Integer getEntityType() {
		return entityType;
	}
	/**
	 * @param entityType the entityType to set
	 */
	protected void setEntityType(Integer entityType) {
		this.entityType = entityType;
	}

	/**
	 * @return the userRead
	 */
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
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
	@XmlElement(required = true)
	public Calendar getCreated() {
		return created;
	}
	/**
	 * @param created the created to set
	 */
	public void setCreated(Calendar created) {
		this.created = created;
	}

	/**
	 * @return the ownerGroup
	 */
	@XmlElement()
	public Group getOwnerGroup() {
		return ownerGroup;
	}
	/**
	 * @param ownerGroup the ownerGroup to set
	 */
	public void setOwnerGroup(Group ownerGroup) {
		this.ownerGroup = ownerGroup;
	}

	/**
	 * @return the owner
	 */
	@XmlElement()
	public User getOwner() {
		return owner;
	}
	/**
	 * @param owner the owner to set
	 */
	public void setOwner(User owner) {
		this.owner = owner;
	}
	
	/**
	 * used only for serialisation
	 * @return the parent ID
	 */
	@XmlElement(required = true)
	public Long getParentID() {
		return parentID;
	}
	/**
	 * used only for serialisation
	 * @param parentID_ the parent id to set
	 */
	protected void setParentID(Long parentID_) {
		parentID = parentID_;
	}
	
	public <T extends File> SummaryItem<T> getSummary() {
		return null;
	}
	
	public String toString() {
		return fileID + ":" + filename;
	}
	
	/**
	 * @return the lastUpdated
	 */
	@XmlElement(required = true)
	@Override
	public Calendar getLastUpdated() {
		return super.getLastUpdated();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((fileID == null) ? 0 : fileID.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		File other = (File) obj;
		if (fileID == null) {
			if (other.fileID != null)
				return false;
		} else if (!fileID.equals(other.fileID))
			return false;
		return true;
	}


	
}
